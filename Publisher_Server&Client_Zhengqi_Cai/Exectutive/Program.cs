using MsgPassingCommunication;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using WpfApp1;
namespace Exectutive
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Console.WriteLine("Command Argument: " + String.Join(" ", args));
            Demo demo = new Demo();
            demo.header();
            var app = new App();
            var mWin = new MainWindow();
            app.Run(mWin);


            mWin.configPathAndServerEp(args);
            mWin.ShowDialog();

            mWin.commandDemoOn();
            mWin.commandGetDirsAndFiles();
            mWin.commandPublish();
            while (mWin.publishing)
            {
                Thread.Sleep(2000);
            }
            mWin.commandDemoDownload();
            while (mWin.downloading)
            {
                Thread.Sleep(2000);
            }
            mWin.commandDemoPopUp();
            mWin.commandDemoOff();
        }
    }
}
