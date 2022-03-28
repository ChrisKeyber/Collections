using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Linq;
using System.Collections;
using System.IO;


namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Type <Stop> to stop the program");
            List<string> collections = new List<string>();
            int i=0;
            while(!collections.Contains("<Stop>"))
            {
                Console.Write("Collections name: ");
                collections.Add(Console.ReadLine());
                if(collections.Contains("<Stop>"))
                {
                    collections.RemoveAt(i);
                    break;
                }
                i++;
            }
            FileStream fs;
            if (File.Exists("Deleted_Reminder"))
            {
                fs = new FileStream("Deleted_Reminders.txt", FileMode.Create, FileAccess.Write);
            }
            else
            {
                fs = new FileStream("Deleted_Reminders.txt", FileMode.Append, FileAccess.Write);
            }
            StreamWriter sw = new StreamWriter(fs);
            using (sw)
            {
                sw.WriteLine("Action date: " + DateTime.Now.ToString("MM/dd/yyyy")+"\n\n");
                foreach (string item in collections)
                {
                    if (Directory.Exists(item))
                    {
                        Directory.Delete(item, true);
                        sw.WriteLine("Your collection: \"{0}\" has been deleted\n", item);
                    }
                    else
                    {
                        Console.WriteLine("\"{0}\" doesn't exist", item);
                    }
                }
            }
            sw.Close();
            Console.WriteLine("You can close the program");
            Console.ReadLine();
        }
    }
}
