///////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - GUI for Project3HelpWPF                      //
// ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package provides a WPF-based GUI for Project3HelpWPF demo.  It's 
 * responsibilities are to:
 * - Provide a display of directory contents of a remote ServerPrototype.
 * - It provides a subdirectory list and a filelist for the selected directory.
 * - You can navigate into subdirectories by double-clicking on subdirectory
 *   or the parent directory, indicated by the name "..".
 *   
 * Required Files:
 * ---------------
 * Mainwindow.xaml, MainWindow.xaml.cs
 * Translater.dll
 * 
 * Maintenance History:
 * --------------------
 * ver 1/1 : 07 Aug 2018
 * - fixed bug in DirList_MouseDoubleClick by returning when selectedDir is null
 * ver 1.0 : 30 Mar 2018
 * - first release
 * - Several early prototypes were discussed in class. Those are all superceded
 *   by this package.
 */

// Translater has to be statically linked with CommLibWrapper
// - loader can't find Translater.dll dependent CommLibWrapper.dll
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using MsgPassingCommunication;
using Path = System.IO.Path;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;

namespace WpfApp1
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            PathTextBlock.Text = ".";
            pathStack_.Push(".");
        }

        private Stack<string> pathStack_ = new Stack<string>();
        private Translater translater;
        private CsEndPoint endPoint_;
        public CsEndPoint serverEndPoint_;

        public bool demo = true;
        //for demo purpuse
        public bool publishing = false;

        //these two to make sure that all plan passing file have received
        public bool downloading = false;
        private List<string> planDownloads = new List<string>();
        //serve as a flag when window closing
        private bool clearing = false;
        private bool closing =false;
        private string clientStorageRoot;
        private string clientStoragePath;
        private Thread rcvThrd = null;
        private Dictionary<string, Action<CsMessage>> dispatcher_
          = new Dictionary<string, Action<CsMessage>>();

        //----< process incoming messages on child thread >----------------

        private void processMessages()
        {
            ThreadStart thrdProc = () =>
            {
                while (true)
                {
                    CsMessage msg = translater.getMessage();
                    Console.WriteLine("Message received: ");
                    msg.show();
                    string msgId = msg.value("command");
                    if (dispatcher_.ContainsKey(msgId))
                        dispatcher_[msgId].Invoke(msg);
                }
            };
            rcvThrd = new Thread(thrdProc);
            rcvThrd.IsBackground = true;
            rcvThrd.Start();
        }
        //----< function dispatched by child thread to main thread >-------

        private void clearDirs()
        {
            DirList.Items.Clear();
        }
        //----< function dispatched by child thread to main thread >-------

        private void addDir(string dir)
        {
            DirList.Items.Add(dir);
        }
        //----< function dispatched by child thread to main thread >-------

        private void insertParent()
        {
            DirList.Items.Insert(0, "..");
        }
        //----< function dispatched by child thread to main thread >-------

        private void clearFiles()
        {
            FileList.Items.Clear();
        }
        //----< function dispatched by child thread to main thread >-------

        private void addFile(string file)
        {
            FileList.Items.Add(file);
        }
        //----< add client processing for message with key >---------------

        private void addClientProc(string key, Action<CsMessage> clientProc)
        {
            dispatcher_[key] = clientProc;
        }

        //----< load getDirs processing into dispatcher dictionary >-------

        private void DispatcherLoadGetDirs()
        {
            Action<CsMessage> getDirs = (CsMessage rcvMsg) =>
            {
                Action clrDirs = () =>
          {
                  clearDirs();
              };
                Dispatcher.Invoke(clrDirs, new Object[] { });
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("dir"))
                    {
                        Action<string> doDir = (string dir) =>
                  {
                      addDir(dir);
                  };
                        Dispatcher.Invoke(doDir, new Object[] { enumer.Current.Value });
                    }
                }
                Action insertUp = () =>
          {
                  insertParent();
              };
                Dispatcher.Invoke(insertUp, new Object[] { });
                if (demo)
                {
                    if ((DirList.Items.Count > 1) && (FileList.Items.Count > 0))
                    {
                        Action dopublish = () =>
                        {
                            commandPublish();
                        };
                        Dispatcher.Invoke(dopublish, new Object[] { });
                    }

                }
            };
            addClientProc("getDirs", getDirs);
        }
        
        //----< load getFiles processing into dispatcher dictionary >------

        private void DispatcherLoadGetFiles()
        {
            Action<CsMessage> getFiles = (CsMessage rcvMsg) =>
            {
                Action clrFiles = () =>
          {
                  clearFiles();
              };
                Dispatcher.Invoke(clrFiles, new Object[] { });
                var enumer = rcvMsg.attributes.GetEnumerator();
                while (enumer.MoveNext())
                {
                    string key = enumer.Current.Key;
                    if (key.Contains("file"))
                    {
                        Action<string> doFile = (string file) =>
                  {
                      addFile(file);
                  };
                        Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
                    }
                }
                if (demo)
                {
                    if((DirList.Items.Count > 1) && (FileList.Items.Count > 0))
                    {
                        Action dopublish = () =>
                        {
                            commandPublish();
                        };
                        Dispatcher.Invoke(dopublish, new Object[] { });
                    }
                    
                }
            };
            addClientProc("getFiles", getFiles);
        }

        //----< load publish processing into dispatcher dictionary >------

        private void DispathcherLoadPublish()
        {
            Action<CsMessage> publish = (CsMessage rcvMsg) =>
            {
                Action doPublish = () =>
                {
                    listProducts.Items.Clear();

                    var enumer = rcvMsg.attributes.GetEnumerator();
                    while (enumer.MoveNext())
                    {
                        string key = enumer.Current.Key;
                        if (key.Contains("product"))
                        {
                            listProducts.Items.Add(enumer.Current.Value);
                        }
                    }
                    publishing = false;
                    Tab.SelectedIndex = 1;
                    txtStatus.Text = "Publishing Done!";
                    if (demo)
                    {
                        commandDemoDownload();
                    }

                };
                Dispatcher.Invoke(doPublish, new Object[] { });               
            };
            addClientProc("publish", publish);
        }

        //----< load downloadSelected processing into dispatcher dictionary >------

        private void DisptacherLoadDownloadSelected()
        {
            Action<CsMessage> downloadSelected = (CsMessage rcvMsg) =>
            {
                if (planDownloads.Count==0)
                {
                    Action clearList = () =>
                    {
                        listDownload.Items.Clear();
                        Tab.SelectedIndex = 2;
                    };
                    Dispatcher.Invoke(clearList, new Object[] { });
                    var enumer = rcvMsg.attributes.GetEnumerator();
                    while (enumer.MoveNext())
                    {
                        string key = enumer.Current.Key;
                        if (key.Contains("download"))
                        {
                            Action<string> addToPlan = (string file) =>
                            {
                                planDownloads.Add(enumer.Current.Value);
                            };
                            Dispatcher.Invoke(addToPlan, new Object[] { enumer.Current.Value });
                        }
                    }
                }
                var filename = Path.GetFileName(rcvMsg.value("file"));
                planDownloads.Remove(filename);
                if(filename.Count(x => x == '.') >= 2)
                {
                    Action<string> addDownload = (string file) =>
                    {
                        listDownload.Items.Add(file);
                    };
                    Dispatcher.Invoke(addDownload, new Object[] { filename });
                }
                
                
                if (planDownloads.Count == 0)
                {
                    Action DownloadDone = () =>
                    {
                        
                        downloading = false;
                        
                        txtStatus.Text = "Downloading Done!";
                        if (demo)
                        {
                            demo = false;
                            commandDemoOff();
                        }
                    };
                    Dispatcher.Invoke(DownloadDone, new Object[] { });
                    
                }
            };
            addClientProc("downloadSelected", downloadSelected);
        }

        //----< load clearAll processing into dispatcher dictionary >------

        private void DispatcherLoadClearAll()
        {
            Action<CsMessage> afterClearAll = (CsMessage rcvMsg) =>
            {
                clearing = false;
                Action clearDone = () =>
                {
                    Tab.SelectedIndex = 0;
                    txtStatus.Text = "Clearing Done!";
                };
                Dispatcher.Invoke(clearDone, new Object[] { });
                //Tab.SelectedIndex = 1;
                if (closing)
                {
                    Action disconnect = () =>
                    {
                        CsMessage msg = new CsMessage();
                        msg.add("to", CsEndPoint.toString(serverEndPoint_));
                        msg.add("from", CsEndPoint.toString(endPoint_));
                        msg.add("command", "quit");
                        Console.Write("\nClient sending ");
                        msg.show();
                        translater.postMessage(msg);
                    };
                    Dispatcher.Invoke(disconnect, new Object[] { });
                    
                }
                
            };
            addClientProc("clearAll", afterClearAll);
        }

        //----< load all dispatcher processing >---------------------------

        private void loadDispatcher()
        {
            DispatcherLoadGetDirs();
            DispatcherLoadGetFiles();
            DispathcherLoadPublish();
            DisptacherLoadDownloadSelected();
            DispatcherLoadClearAll();
        }

        public void configPathAndServerEp(string[] args)
        {
            serverEndPoint_ = CsEndPoint.fromString(args[1]);
            if (args[1] != ".")
            {
                PathTextBlock.Text = args[2];
                pathStack_.Push(args[2]);
            }
        }

        //----< start Comm, fill window display with dirs and files >------

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Demo demoObj = new Demo();
            demoObj.header();
            string[] args = Environment.GetCommandLineArgs();
            Console.WriteLine("Command Argument: " + String.Join(" ", args));

            demoObj.req3();
            demoObj.req4();
            demoObj.req5();
            demoObj.req6();
            demoObj.req7();
            demoObj.req8();
            configPathAndServerEp(args);

            configClientSide();

            // start ClientComm
            translater = new Translater();
            translater.listen(endPoint_);
            // load dispatcher
            loadDispatcher();
            // start processing messages
            processMessages();
            if (demo)
            {
                commandDemoOn();
            }
            commandGetDirsAndFiles();
            
        }

        private void configClientSide()
        {
            endPoint_ = new CsEndPoint();
            endPoint_.machineAddress = "localhost";
            endPoint_.port = FreeTcpPort();
            this.Title = "Client " + CsEndPoint.toString(endPoint_);
            string srcFPath = Path.GetDirectoryName(new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileName());
            clientStorageRoot = Path.GetFullPath(srcFPath + "\\..\\ClientStorage");
            //specific storagepath for this client
            clientStoragePath = clientStorageRoot + "\\" + endPoint_.machineAddress + endPoint_.port.ToString();
            if (Directory.Exists(clientStoragePath))
            {
                Directory.Delete(clientStoragePath, true);
            }
            //create folder hierarchy
            Directory.CreateDirectory(clientStoragePath);
            Directory.CreateDirectory(clientStoragePath + "\\css");
            Directory.CreateDirectory(clientStoragePath + "\\js");
            Directory.CreateDirectory(clientStoragePath + "\\notFounds");
            Directory.CreateDirectory(clientStoragePath + "\\HTML");
            txtFDirOut.Text = clientStoragePath;
        }

        public void commandDemoOff()
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint_));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "demoOff");
            Console.Write("\nClient sending ");
            msg.show();
            translater.postMessage(msg);
        }

        public void commandDemoOn()
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint_));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "demoOn");
            Console.Write("\nClient sending ");
            msg.show();
            translater.postMessage(msg);
        }

        public void commandGetDirsAndFiles()
        {
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint_));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "getDirs");
            msg.add("path", pathStack_.Peek());
            Console.Write("\nClient sending ");
            msg.show();
            translater.postMessage(msg);
            msg.remove("command");
            msg.add("command", "getFiles");
            Console.Write("\nClient sending ");
            msg.show();
            translater.postMessage(msg);
        }

        //----< get available port for the listenersocket of this client >----------------

        private int FreeTcpPort()
        {
            TcpListener l = new TcpListener(IPAddress.Loopback, 0);
            l.Start();
            int port = ((IPEndPoint)l.LocalEndpoint).Port;
            l.Stop();
            return port;
        }

        //----< respond to mouse double-click on dir name >----------------

        private void DirList_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            // build path for selected dir
            string selectedDir = (string)DirList.SelectedItem;
            if (selectedDir == null)
                return;
            string path;
            if (selectedDir == "..")
            {
                if (pathStack_.Count > 1)  // don't pop off "Storage"
                    pathStack_.Pop();
                else
                    return;
            }
            else
            {
                path = pathStack_.Peek() + "/" + selectedDir;
                pathStack_.Push(path);
            }
            // display path in Dir TextBlcok
            PathTextBlock.Text = pathStack_.Peek();

            commandGetDirsAndFiles();
        }

        //----< respond to click on convert button >----------------

        private void BtnPublish_Click(object sender, RoutedEventArgs e)
        {
            commandPublish();
        }

        public void commandPublish()
        {
            if (publishing)
            {
                txtStatus.Text = "Please do not reclick the button when publishing...";
            }
            else
            {
                publishing = true;
                txtStatus.Text = "Publishing...Please wait.";
                CsMessage msg = new CsMessage();
                msg.add("to", CsEndPoint.toString(serverEndPoint_));
                msg.add("from", CsEndPoint.toString(endPoint_));
                msg.add("command", "publish");
                msg.add("path", pathStack_.Peek());
                Console.Write("\nClient sending ");
                msg.show();
                translater.postMessage(msg);
            }
        }

        //----< respond to click on download button >----------------

        private void BtnDownload_Click(object sender, RoutedEventArgs e)
        {
            commandDownload();
        }

        public void commandDownload()
        {
            if (downloading)
            {
                txtStatus.Text = "Please do not reclick when downloading...";
            } 
            else
            {
                if (listProducts.SelectedItems.Count == 0)
                {
                    txtStatus.Text = "Please choose at least one file to download!";
                }
                else
                {
                    downloading = true;
                    planDownloads.Clear();
                    txtStatus.Text = "Downloading...Please wait.";
                    var selected = listProducts.SelectedItems;
                    CsMessage msg = new CsMessage();
                    msg.add("to", CsEndPoint.toString(serverEndPoint_));
                    msg.add("from", CsEndPoint.toString(endPoint_));
                    msg.add("command", "downloadSelected");
                    msg.add("saveFilePath", txtFDirOut.Text + "\\HTML");
                    for (int i = 0; i < selected.Count; i++)
                    {
                        msg.add("download-product" + i, selected[i].ToString());
                    }
                    Console.Write("\nClient sending ");
                    msg.show();
                    translater.postMessage(msg);
                }
            }
        }

        public void commandDemoDownload()
        {

            int i = 0;
            while (i < listProducts.Items.Count)
            {
                listProducts.SelectedItems.Add(listProducts.Items[i]);
                i += 2;
            }


            commandDownload();

        }

        public void commandDemoPopUp()
        {
            //var li = listDownload.ItemContainerGenerator.ContainerFromIndex(0);
            //li.RaiseEvent(new RoutedEventArgs(System.Windows.Controls.Button.MouseDoubleClickEvent));

        }

        //----< respond to double-click on download firename >----------------

        private void ListDownload_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            string selStr = listProducts.SelectedItem.ToString();
            selStr = System.IO.Path.Combine(clientStoragePath + "\\HTML", selStr);
            System.Diagnostics.Process.Start(selStr);
        }

        //----< respond to click on restart button >----------------

        private void BtnRestart_Click(object sender, RoutedEventArgs e)
        {
            txtStatus.Text = "Clearing client temp files on server...Please wait.";
            clearing = true;
            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint_));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "clearAll");
            Console.Write("\nClient sending ");
            msg.show();
            translater.postMessage(msg);
        }

        private void Browse_Click(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog browser = new System.Windows.Forms.FolderBrowserDialog();
            if (browser.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtFDirOut.Text = browser.SelectedPath;
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            closing = true;
            btnRestart.RaiseEvent(new RoutedEventArgs(System.Windows.Controls.Button.ClickEvent));
            
            
        }


    }
}
