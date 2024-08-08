using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class TruthTable : Method
    {
        bool[][] table;
        int kb_model = 0;
        bool entail = true;
        public TruthTable(Knowledge_Base kb) : base(kb) { }
        public override void Run(string query)
        {
            List<string> literal = new List<string>();
            foreach(Proposition proposition in Kbase.Propositions) // get a list of all literals that are not part of KB
            {
                if (proposition is Literal && !Kbase.KB.Contains(proposition.Name))
                {
                    literal.Add(proposition.Name);
                }
            }
            table = new bool[Convert.ToInt32(Math.Pow(2, literal.Count))][]; // create the table array with length equal the square of the number of literal
            for (int i = 0; i < (1 << literal.Count); i++) // loop through the table
            {
                Kbase.Facts.Clear();
                foreach (string given in Kbase.KB) // The literals in KB dont need to be assigned truth value and are assumed facts
                {
                    if (Kbase.Get(given) is Literal)
                    {
                        Kbase.AddFact(given);
                    }
                }
                table[i] = new bool[Kbase.Propositions.Count + 1];
                for (int j = 0; j < literal.Count; j++)
                {
                    if ((i & (1 << j)) != 0) // assign truth value to literals using binary counter method
                    {
                        Kbase.AddFact(literal[j]);
                    }
                }
                for (int k = 0; k < Kbase.Propositions.Count; k++)
                {
                    table[i][k] = Kbase.Propositions[k].IsTrue(); // populate the table with truth value of all propositions
                }
                bool kb = true;
                foreach(string condition in Kbase.KB) // check if the KB is true given the current truth assignment
                {
                    if (!Kbase.Get(condition).IsTrue())
                    {
                        kb = false;
                    }
                }
                table[i][table[i].Length - 1] = kb;
                if (kb)
                {
                    kb_model++;
                    if (!Kbase.Get(Kbase.Goal).IsTrue()) // if sentence is false while kb is true then kb does not entail the sentence
                    {
                        entail = false;
                    }
                }
            }
        }

        public override void Display() // YES or NO followed by the number of kb models
        {
            if(entail)
            {
                Console.Write("YES: ");
                Console.Write(kb_model);
            }
            else
            {
                Console.Write("NO");
            }
        }
    }
}
