using System;

namespace Program
{
    public class Program
    {
        public static void Main(string[] args)
        {
            using (var server = new AsyncHttpServer())
            {
                server.Start("http://+:8080/");
                Console.ReadKey(true);
            }
        }
    }
}

/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Program
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Запускаем курсач...");
            Process cur = new Process();
            cur.StartInfo.FileName = "C:/Users/user/Documents/Visual Studio 2017/Projects/CursachConsoleVersionC++/Debug/CursachConsoleVersionC++.exe";
            cur.Start();
            Console.WriteLine("запущен");
            Console.ReadLine();
            try
            {
                cur.Kill();
            }
            finally { }
        }
    }
}*/
