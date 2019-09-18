using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    class Demo
    {
        public void header()
        {
            Console.WriteLine("===========Project4 Remote Code Page Management --Zhengqi Cai============");
        }

        public void req3()
        {
            Console.WriteLine("\nDemonstrate Req #3, assemble working parts from Projects #1, #2, and #3 into a Client-Server configuration");
            Console.Write("This project is composed of two part, GUI(Client) and ServerProtoType. GUI includes ");
            Console.Write("Translater for wrapping the Comm system, which from the model of Proejct3. ServerProtoType ");
            Console.Write("includes IComm facilities, which is created in Proj1 and Proj2 and polished in Proj3.");
            Console.WriteLine("As you can see in the auto test, clients could send getDirs and getFiles without blocking.");

        }

        public void req4()
        {
            Console.WriteLine("\nDemonstrate Req #4, provide GUI that supports navigating remote directories and displaying the conversion results.");
            Console.Write("The Client GUI you see is built by WPF. To navigate remote directories please double-click some directory to check.");
            Console.Write("To display the conversion reuslt, you could double-click some product in the Display tab after publishing and downloading, ");
            Console.WriteLine("and it will show in default browser. You may check both after the auto test.");
        }

        public void req5()
        {
            Console.WriteLine("\nDemonstrate Req #5, provide message designs appropriate for this application.");
            Console.WriteLine("You may see the \"MessageSystem.PNG\" in this folder to have a general view.");
        }

        public void req6()
        {
            Console.WriteLine("\nDemonstrate Req #6, support converting source code in the server and, with a separate request, transferring one or more converted files back to the local client.");
            Console.Write("You can click the \"publish\" button to create published files in server side and check them in .\\ServerStorage\\ClientTemp\\localhostxxxx.");
            Console.WriteLine("These files server as temp files and would be deleted when you click \"Restart\" button or close the GUI.");
            Console.Write("To the download files, go to published files tab and select files in the list, then click \"Download\" button and it would download");
            Console.WriteLine("all the selected files in .\\ClientStorage\\localhostxxxx. These file would not be deleted automatically.");
        }

        public void req7()
        {
            Console.WriteLine("\nDemonstrate Req #7, demonstrate correct operations for two or more concurrent clients.");
            Console.Write("The Run.bat is designed to install two client GUI with the same operations required in req8. ");
            Console.Write("You may find the files generated in both ServerStorage and downloaded in ClientStorage folder concurrently in the auto test.");
        }

        public void req8()
        {
            Console.WriteLine("\nDemonstrate Req #8, an automated test that accepts the server url and remote path to Proj4 on its command line, invokes the Code Publisher, through its interface, to convert all the *.h and *.cpp files, and then opens the Client GUI's Display view.");

        }
    }
}
