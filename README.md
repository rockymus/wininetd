# wininetd
Guide for starting isolated processes on your network with wininetd

1. Download wininetd and netcat from following links : http://xmailserver.org/wininetd.html https://eternallybored.org/misc/netcat/ and clone this repository.

2. Extract .zip files in directories of your choice

3. Start cmd as administrator and position yourself in directory where you extracted wininetd.zip (Example: *C:\Users\username\Desktop\wininetd-0.7\Release*)

4. Install wininetd with the following command : **wininetd.exe --install**

5. Open *C:\Wndows* in File Explorer and check for file called **wininetd.conf**. If not there create it and open it. The configuration file is very simple and it is composed by multiple lines following this format:

   **PORT    USER:PASS    PATH**

   Where **PORT** is the port number the server has to listen for incoming connections, **USER:PASS** is the username and password separated by a colon ( : ) character and **PATH** is the path of the binary image to be executed and its command line parameters. It is possible to not specify any user (and hence having the new process to run with the service user credentials) by specifying **none** as **USER:PASS**. Add one more character in wininetd.conf because wininetd will removes the last character.

   Example: 
   
   202 User1:1234 c:\test_program.exe
   
   203 User2:12345 c:\test_program.exee
   
6. You can check if desired port is available with cmd and **netstat -an | find ":8080"** where 8080 is the desired port. test_program.exe is the program from this repository which takes a path to some .txt file and prints it. You need to position it in the same directory as you have written in wininetd.conf.

7. Creating users for isolation is easy. Go to Run -> write lusrmgr.msc -> Ok -> select Users -> right click in the right window and select New user. Set username and password for your user. Repeat for second user. (My example: User1:1234, User2:12345). Left click on the Group folder in left window, create it and add your users to that group.

8. We need to change some Windows settings. Go to Run -> write secpol.msc -> select Local Policy -> select User Rights Assignment and double click on **Logon as a batch job**. In new window select **Add User or group** -> select Object types and check Groups -> Ok ->click on Find Now and find your created group and add it. Save changes. Do the same for **Replace a process level token**.

9. Now create two .txt files write something in both of them (Example: user1.txt, user2.txt). We need to change permissions for both of them. Our main idea is that when we start a process as User1 we can read user1.txt, but can't user2.txt. Right click user1.txt -> Properties -> Security tab -> Edit -> select User2 -> Deny : Full control. Do the same thing for user2.txt but deny full control for User1. 

10. Now we can test it. Open cmd as administrator and position yourself in wininetd/Release directory. Start wininetd with **wininetd --debug**. Open second cmd and position yourself in netcat directory. Run command **nc localhost port** where port is one of two which you specified in wininetd.conf. Example: **nc localhost 202** runs test_program.exe as User1.  Now give it the path to user1.txt and you should see the content. Now repeat the process for user2.txt and you should not see its content. If everything works you should be set.
