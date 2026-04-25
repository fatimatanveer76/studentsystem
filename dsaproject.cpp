#include <iostream>
#include <fstream>
// include <string>
using namespace std;

/* ================= FILE CLASS ================= */
class File
{
private:
    static const int max_line = 1000; //maximum lines a file can have
    string lines[max_line];
    int lineCount;

public:
    File()
    {
        lineCount = 0;
    }
    // LOAD FILE INTO ARRAY
    bool loadFile(const string &filepath)  //it will take file path as a parameter
    {
        ifstream file(filepath);
        if (!file.is_open())
            return false;

        lineCount = 0;
        string temp;
        while (getline(file, temp) && lineCount < max_line)  //it will read the file line by line and store each line  in array until maxline not reached
        {
            lines[lineCount] = temp;
            lineCount++;
        }
        file.close();
        return true;
    }
// SAVE ARRAY INTO FILE
    bool saveFile(const string &filepath)
    {
        ofstream file(filepath);
        if (!file.is_open())
            return false;

        for (int i = 0; i < lineCount; i++)
            file << lines[i] << "\n";

        file.close();
        return true;
    }
// SAVE ARRAY INTO FILE
   /*int Fileindex(const string &topic_name)  //this will search the topic through given keyword
    {
        for (int i = 0; i < lineCount; i++)
        {
            if (lines[i] == topic_name)
                return i;
        }
        return -1;
    }*/
  /* int Fileindex(const string &topic_name)
{
    for (int i = 0; i < lineCount; i++)
    {
        string topic = "";
        // Extract topic from line
        for (int j = 0; j < lines[i].length() && lines[i][j] != '|'; j++)
            topic += lines[i][j];

        if (topic == topic_name)
            return i;
    }
    return -1;
}
*/
//user friendly
int Fileindex(const string &topic_name)
{
    for (int i = 0; i < lineCount; i++)
    {
        // --- 1. Extract Topic from File Line ---
        string topicFromFile = "";
        for (int j = 0; j < lines[i].length() && lines[i][j] != '|'; j++)
        {
            topicFromFile += lines[i][j];
        }

        // --- 2. Manual Cleaning (Spaces & Case) ---
        // Hum do naye temporary strings banayenge compare karne ke liye
        string cleanFileTopic = "";
        string cleanUserInput = "";

        // File se nikale gaye topic ko clean karein
        int startF = 0, endF = topicFromFile.length() - 1;
        while (startF <= endF && topicFromFile[startF] == ' ') startF++; // Start spaces skip
        while (endF >= startF && topicFromFile[endF] == ' ') endF--;     // End spaces skip
        
        for (int k = startF; k <= endF; k++) {
            char ch = topicFromFile[k];
            if (ch >= 'A' && ch <= 'Z') ch = ch + 32; // Lowercase conversion
            cleanFileTopic += ch;
        }

        // User ke input (topic_name) ko clean karein
        int startU = 0, endU = topic_name.length() - 1;
        while (startU <= endU && topic_name[startU] == ' ') startU++;
        while (endU >= startU && topic_name[endU] == ' ') endU--;

        for (int k = startU; k <= endU; k++) {
            char ch = topic_name[k];
            if (ch >= 'A' && ch <= 'Z') ch = ch + 32;
            cleanUserInput += ch;
        }

        // --- 3. Final Comparison ---
        if (cleanFileTopic == cleanUserInput && cleanUserInput != "")
        {
            return i;
        }
    }
    return -1;
}
  // append topic at the end of file
    bool appendToFile(const string &filepath, const string &data)
    {
        ofstream file(filepath, ios::app);
        if (!file) return false;
        file << data << "\n";
        file.close();
        return true;
    }
   // delete function(load function,savefile function)
    bool deleteLine(const string &filepath, const string &deletedtopic)
    {
        if (!loadFile(filepath)) return false;

        int idx = Fileindex(deletedtopic);
        if (idx == -1) return false;

        for (int i = idx; i < lineCount - 1; i++)
            lines[i] = lines[i + 1];

        lineCount--;
        return saveFile(filepath);
    }
   // update function(load function,savefile function)
    bool updateSingleLine(const string &filepath, const string &oldtopic, const string &newtopic)
    {
        if (!loadFile(filepath)) return false;

        int idx = Fileindex(oldtopic);
        if (idx == -1) return false;

        lines[idx] = newtopic;
        return saveFile(filepath);
    }
  // SEARCH AND GET INDEX (used by Admin searchTopic)
    int findIndex(const string &filepath, const string &search_word)
    {
        if (!loadFile(filepath)) return -1;
        return Fileindex(search_word);
    }

    string getLine(const string &filepath, int index)
    {
        
        if (index >= 0 && index < lineCount)
            return lines[index];
        return "";
    }

    void displayTopic(const string &filepath)
    {
       if (lineCount == 0)
    {
        cout << "\nNo topics to display!\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "              TOPICS LIST\n";
    cout << "=========================================\n";

    for (int i = 0; i < lineCount; i++)
    {
        // Extract topic only (before '|')
        string topic;
        int j = 0;
        while (j < lines[i].length() && lines[i][j] != '|')
        {
            topic += lines[i][j];
            j++;
        }
        cout << i + 1 << ". " << topic << endl;
    }
    cout << "=========================================\n";
   }
};

/* ================= ADMIN CLASS ================= */

class Admin
{
private:
    File fm;
    string filePath;

public:
    Admin(string file)
    {
        filePath = file;
    }
    void showsubjects()
    {
    	cout << "=========================================\n";
        cout << "             SELECT SUBJECT\n";
        cout << "=========================================\n";
        cout << "  1. Programming Fundamentals (PF)\n";
        cout << "  2. Object Oriented Programming (OOP)\n";
        cout << "  3. Data Structures (DSA)\n";
        cout << "  4. Ideology\n";
        cout << "  5. Digital Logic Design (DLD)\n";
        cout << "-----------------------------------------\n";
        cout << "  Enter choice: ";
    }
    


    bool start()
    {
        showsubjects();
        int c;
        cin >> c;
        string currFile;

        if (c == 1) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\PF.txt";
        else if (c == 2) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\oop.txt";
        else if (c == 3) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\DSA.txt";
        else if (c == 4) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\ideology.txt";
        else if (c == 5) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\DLD.txt";
        else return false;
        filePath = currFile; 
        return fm.loadFile(currFile);
    }
    // ADD TOPIC
    void addTopic()
    {
        cin.ignore();
        string topic, content;
        cout << "\n=========================================\n";
        cout << "               ADD NEW TOPIC\n";
        cout << "=========================================\n";
        cout << "Enter Topic: ";
        getline(cin, topic);
        cout << "Enter Content: ";
        getline(cin, content);
        string data = topic + "|" + content;
        fm.appendToFile(filePath, data);
        cout << " Topic added successfully!\n";
    }
   //UPDATE TOPIC
    void updateTopic()
    {
        fm.displayTopic(filePath);
        cin.ignore();

        string oldLine, newLine;
        cout << "Old line: ";
        getline(cin, oldLine);
        cout << "New line: ";
        getline(cin, newLine);

       if (fm.updateSingleLine(filePath, oldLine, newLine))
       {
       	 cout << " Topic updated successfully!\n";
	   }
	   else
	   {
	   	 cout << " Update failed. Topic not found.\n";
	   }
    }
   // DELETE TOPIC
    void deleteTopic()
    {
        fm.displayTopic(filePath);
        cin.ignore();

        string del;
        cout << "Delete line: ";
        getline(cin, del);

       if(fm.deleteLine(filePath, del))
       {
       	cout << " Topic deleted successfully!\n";
       }
        else
        {
		    cout << " Delete failed. Topic not found.\n";
	    }
    }
  //SEARCH TOPIC
    void searchTopic()
    {
        cin.ignore();
        string key;
        cout << "Search: ";
        getline(cin, key);

        int idx = fm.findIndex(filePath, key);
        if (idx != -1)
        {
		 cout << "\n Found Topic: " << fm.getLine(filePath, idx) << endl;
        }
        else
        {
		 cout << "Not found\n";
        }
    }
  //MENU
    void showMenu(Admin &A)
    {
        int ch;
        do
        {
        	cout << "\n=========================================\n";
            cout << "               ADMIN DASHBOARD\n";
            cout << "=========================================\n";
            cout << "  1. Add Topic\n";
            cout << "  2. Delete Topic\n";
            cout << "  3. Search Topic\n";
            cout << "  4. Update Topic\n";
            cout << "  5. Show All Topics\n";
            cout << "  6. Exit\n";
            cout << "-----------------------------------------\n";
            cout << "  Enter choice: ";
            cin >> ch;
            switch (ch)
            {
            case 1: A.addTopic(); break;
            case 2: A.deleteTopic(); break;
            case 3: A.searchTopic(); break;
            case 4: A.updateTopic(); break;
            case 5: fm.displayTopic(filePath); break;
            }
        } while (ch != 6);
    }
};
//QUEUE CLASS
class Queue
{
private:
    string *arr;
    int maxSize;
    int currSize;
    int front;
    int back;
    int lastIndex;

public:
    Queue()
    {
        maxSize = 100;
        arr = new string[maxSize];
        currSize = 0;
        front = 0;
        back = 0;
        lastIndex = -1;
    }

    ~Queue()
    {
        delete[] arr;
    }

    bool enqueue(string elem)
    {
        if (currSize == maxSize) return false;
        arr[back] = elem;
        lastIndex = back;
        back = (back + 1) % maxSize;
        currSize++;
        return true;
    }

    bool showLast(string &elem)
    {
        if (lastIndex == -1) return false;
        elem = arr[lastIndex];
        return true;
    }
   bool showAll()
   {
      if (currSize == 0)
      {
         cout << "\nNo history yet.\n";
         return false;  // nothing to show
      }

      cout << "\n===== Previous Answers =====\n";
      for (int i = 0; i < currSize; i++)
      {
      	cout << i + 1 << ". " << arr[(front + i) % maxSize] << endl;
        cout << "============================\n";
	  }
        
    return true;  // history displayed
   }
};

/* ================= STUDENT CLASS ================= */
class Student
{
private:
    File Fm;
    Queue q;
    string currFile;
    string topics[100];
    int topicCount;
public:
	Student()
	{ 
	  topicCount = 0; 
	}
    void Showsubjects()
    {
        cout << "\n=========================================\n";
        cout << "             AVAILABLE SUBJECTS\n";
        cout << "=========================================\n";
        cout << "1. Programming Fundamentals (PF)\n";
        cout << "2. Object-Oriented Programming (OOP)\n";
        cout << "3. Data Structures & Algorithms (DSA)\n";
        cout << "4. Ideology\n";
        cout << "5. DLD\n";
        cout << "=========================================\n";
    }

    bool Start()
    {
        Showsubjects();
        int c;                    
        cin >> c;

        if (c == 1) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\PF.txt";
        else if (c == 2) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\oop.txt";
        else if (c == 3) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\DSA.txt";
        else if (c == 4) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\ideology.txt";
        else if (c == 5) currFile = "C:\\Users\\Elitebook\\Desktop\\studentsystem\\DLD.txt";
        else return false;

         
          if (Fm.loadFile(currFile))
          {
          	extractTopicsFromFile(); 
			insertionSortTopics();  
          	displayTopics(); 
          	return true;
		  }
        return false;
    }
   

    void extract(const string &line, string &topic, string &content)
    {
        topic = "";
        content = "";
        int i = 0;
        while (i < line.length() && line[i] != '|')
        {
            topic += line[i];
            i++;
        }
        i++;
        while (i < line.length())
        {
            content += line[i];
            i++;
        }
    }
    void extractTopicsFromFile()
    {
        topicCount = 0;
        for (int i = 0; i < 1000; i++)
        {
            string line = Fm.getLine(currFile, i);
            if (line == "") break;

            string topic, content;
            extract(line, topic, content); // separate function for topic/content
            topics[topicCount++] = topic;
        }
    }
     // Simple insertion sort for topics
    void insertionSortTopics()
    {
        for (int i = 1; i < topicCount; i++)
        {
            string key = topics[i];
            int j = i - 1;
            while (j >= 0 && topics[j] > key)
            {
                topics[j + 1] = topics[j];
                j--;
            }
            topics[j + 1] = key;
        }
    }
     void displayTopics()
    {
    	cout << "\n=========================================\n";
        cout << "                 TOPICS\n";
        cout << "=========================================\n";
        for (int i = 0; i < topicCount; i++)
        {
            cout << i + 1 << ". " << topics[i] << endl;
        }
        cout << "=========================================\n";
    }
//ASK QS
void askQuestion()
{
    
     cin.ignore();
	 string topic; 
	 while (true) // loop keeps asking questions 
	 { 
	    cout << "\nEnter question (or type EXIT to quit): ";
	    getline(cin, topic); // exit condition 
		if (topic == "EXIT" || topic == "exit") 
		{ 
	    	cout << "Exiting question mode...\n"; 
		   break; 
		} 
		int idx = Fm.Fileindex(topic); 
		if (idx == -1)
		 { 
		   cout << "Not found. Try again.\n"; 
		   continue; // ask question again
		 }
		  string line = Fm.getLine(currFile, idx);
	       string t, c;
	       extract(line, t, c);
	       q.enqueue(c);
		   q.showAll(); // save answer in history
		   cout << c << endl; // show answer 
	     }


}

// FOR SHOWING LAST ANS
    void showLastAnswer()
    {
        string last;
        if (q.showLast(last))
        {
        	cout << "Last Answer: " << last << endl;
		}
            
    }
};

/* ================= AUTH CLASS ================= */
class Auth
{
private:
    string username, password, role;

public:
    void signup()
    {
        fstream file;   // LOCAL FILE (SAFE)

        
        cout << "\n=========================================\n";
        cout << "               SIGN UP\n";
        cout << "=========================================\n";
        cout << "Enter Username: ";
        getline(cin, username);

        int count;
        do
        {
            cout << "Enter Password (exactly 8 characters): ";
            getline(cin, password);

            count = 0;
            for (int i = 0; password[i] != '\0'; i++)
                count++;

            if (count != 8)
                cout << "Password must be exactly 8 characters!\n";

        } while (count != 8);

        cout << "Enter Role (student/admin): ";
        getline(cin, role);

        file.open("users.txt", ios::out | ios::app);
        file << username << "*" << password << "*" << role << endl;
        file.close();

        cout << "Account created successfully!\n";
        cout << "Password is: ********\n";
    }

    void login()
    {
        fstream file;   // LOCAL FILE (SAFE)
        string inputUser, inputPass;
        bool found = false;
        int count = 0;
        cout << "\n=========================================\n";
        cout << "               LOGIN\n";
        cout << "=========================================\n";
        cout << "Username: ";
        getline(cin, inputUser);

        cout << "Enter Password (8 characters): ";
        getline(cin, inputPass);

        for (int i = 0; inputPass[i] != '\0'; i++)
            count++;

        if (count != 8)
        {
            cout << "Password must be exactly 8 characters!\n";
            return;
        }

        file.open("users.txt", ios::in);
        if (!file)
        {
            cout << "User file not found!\n";
            return;
        }

        while (getline(file, username, '*') && getline(file, password, '*') &&getline(file, role))
        {
            if (username == inputUser && password == inputPass)
            {
                found = true;
                cout << "Login successful!\n";
                cout << "Role: " << role << endl;
                if (role == "admin")
                {
                    Admin A("");
                    if (A.start())        // subject selected successfully
                    {
                        A.showMenu(A);    // now admin can add/delete/search/update
                    }
                }
                else if (role == "student")
                {
                   Student s;
                  if (s.Start())
                 {
                    s.askQuestion();
                    s.showLastAnswer();
                  }
                }
                break;
            }
        }

        file.close();

            if (!found)
            {
               int ch;
               cout << "\nInvalid username or password!\n";
               cout << "1. Try Again\n";
               cout << "2. Forget Password\n";
               cout << "3. Back to Main Menu\n";
               cout << "Enter choice: ";
               cin >> ch;
               cin.ignore(1000, '\n');
			    if (ch == 1)
			    {
                  login();
                }
                 else if (ch == 2)
                 {
                 	
				    forgetPassword();
                 }
                 else 
                 {
                 	menu();
				 }
			}
    }

    void forgetPassword()
    {
    	cin.ignore(1000,'\n'); 
        fstream file;   // LOCAL FILE (SAFE)
        string searchUser;
        bool found = false;

        cout << "\n=========================================\n";
        cout << "             FORGOT PASSWORD\n";
        cout << "=========================================\n";
        cout << "Enter Username: ";
        getline(cin, searchUser);

        file.open("users.txt", ios::in);
        if (!file)
        {
            cout << "User file not found!\n";
            return;
        }

        while (getline(file, username, '*') && getline(file, password, '*') &&getline(file, role))
        {
            if (username == searchUser)
            {
                cout << "Account Found!\n";
                cout << "Password: ********\n";
                cout << "Role: " << role << endl;
                found = true;
                break;
            }
        }

        file.close();

        if (!found)
            {
            	cout << "? No account found!\n";
            }
    }

    void menu()
    {
        int choice;
        do
        {
            cout << "\n=========================================\n";
            cout << "            STUDENT SYSTEM MENU\n";
            cout << "=========================================\n";
            cout << "1. Sign Up\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "-----------------------------------------\n";
            cout << "Enter choice: ";
            cin >> choice;
             if (cin.fail())
             {
               cin.clear();                 // clear fail state
               cin.ignore(1000, '\n');      // remove bad input
               cout << "Invalid input! Enter numbers only.\n";
               continue;                    // restart menu safely
             }
            cin.ignore(1000, '\n');   // BUFFER FIX

            switch (choice)
            {
            case 1: signup(); break;
            case 2: login(); break;
            case 3: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
            }

        } while (choice != 4);
    }
};

/* ================= MAIN ================= */
int main()
{
    Auth system;
    system.menu();
    return 0;
}

