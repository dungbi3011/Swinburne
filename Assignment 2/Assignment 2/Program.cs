
using System;
using System.Diagnostics;
using System.Drawing;
using System.Text.RegularExpressions;

namespace Assignment2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            if (args.Length >= 2)
            {
                StreamReader file = null;
                if (File.Exists("inputs" + "\\" + args[1]))
                {
                    file = new StreamReader("inputs" + "\\" + args[1]);
                }
                else if (File.Exists(args[1]))
                {
                    file = new StreamReader(args[1]);
                }
                if (file != null)//check if a valid text file was entered
                {
                    file.ReadLine();
                    string[] kb = file.ReadLine().Split(";");
                    file.ReadLine();
                    string goal = file.ReadLine().Trim();
                    file.Close();
                    Knowledge_Base knowledgebase = new Knowledge_Base();
                    Method method = null;
                    if (args[0] == "TT")   // choose a method
                    {
                        method = new TruthTable(knowledgebase);
                    }
                    else if (args[0] == "FC")
                    {
                        method = new ForwardChaining(knowledgebase);
                    }
                    else if (args[0] == "BC")
                    {
                        method = new BackwardChaining(knowledgebase);
                    }
                    else if (args[0] == "RB")
                    {
                        method = new ResolutionBasedTheoremProver(knowledgebase);
                    }
                    if(method != null)  // if a supported method was chosen 
                    {
                        knowledgebase.Setup(kb, goal);
                        method.Run(knowledgebase.Goal);
                        method.Display();
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.DarkRed;
                        Console.WriteLine("Unsupported method");
                        Console.ForegroundColor = ConsoleColor.Gray;
                    }
                }
                else //cant find the text file
                {
                    Console.ForegroundColor = ConsoleColor.DarkRed;
                    Console.WriteLine("Cannot find " + args[1]);
                    Console.ForegroundColor = ConsoleColor.Gray;
                }
            }
            else //not enough arguments
            {
                Console.ForegroundColor = ConsoleColor.DarkRed;
                Console.WriteLine("Must have at least 2 arguments");
                Console.ForegroundColor = ConsoleColor.Gray;
            }
        }

    }
}
