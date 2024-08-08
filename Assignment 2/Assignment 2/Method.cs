using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public abstract class Method
    {
        Knowledge_Base kbase;
        public Method(Knowledge_Base kb)
        {
            kbase = kb;
        }

        public abstract void Run(string query); // Each method will provide its own implementation

        public virtual void Display() // Some method will have a diffrent way of displaying the result
        {
            if (Kbase.IsFact(Kbase.Goal)) // print YES if the goal is a fact
            {
                Console.Write("YES: ");
                foreach (string fact in kbase.Facts) // print all infered facts
                {
                    Console.Write(fact + ", ");
                }
            }
            else // print NO if the goal is not a fact
            {
                Console.Write("NO");
            }
        }

        public Knowledge_Base Kbase { get { return kbase; } }
    }
}
