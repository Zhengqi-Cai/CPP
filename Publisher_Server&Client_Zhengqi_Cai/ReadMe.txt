Remote Publisher Server&Client

This application contains both CodePublish Server developed in native C++ and Client interface with WPF(C#). Clients could navigate remote directories on the server to find a project for conversion, and transferring them back for publication. Server is designed to be able to handle concurrent client requests and convert target src files to functional HTML files after parse analysis.

You may simulate this C-S model on one computer, 'ServerStorage' folder includes temporary files for each clients, and 'ClientStorage' is the default local storage directory for clients.

Compile src files in local compiler and then double click run.bat to run. Or see the 'App_Snapshot.pdf' for more detail.
For the implementation, please see 'Comm Protocol.png' and 'Core_Package_Structure.png'.
