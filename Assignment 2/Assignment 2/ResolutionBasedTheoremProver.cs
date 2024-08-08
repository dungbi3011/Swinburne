using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class ResolutionBasedTheoremProver : Method
    {
        List<string> clauses = new List<string>();
        bool contradiction = false;
        public ResolutionBasedTheoremProver(Knowledge_Base kb) : base(kb) { }
        public override void Run(string query)
        {
            foreach (string given in Kbase.KB) // convert the KB to conjunctive normal form
            {
                ToCNF(given);
            }
            ToCNF(Kbase.Parse("~(" + Kbase.Goal + ")")); // convert the negation of the sentence to conjunctive normal form
            Kbase.Facts.Clear();
            foreach (string disjunction in clauses) // add the CNF propositions to facts
            {
                Kbase.AddFact(disjunction);
            }
            clauses.Clear();
            int factcount = -1;
            while (factcount < Kbase.Facts.Count) // limit to 50 iterations
            {
                factcount = Kbase.Facts.Count;
                for (int i = 0; i < factcount; i++)
                {
                    for (int j = i + 1; j < factcount; j++)
                    {
                        if (ApplyRule(Kbase.Facts[i], Kbase.Facts[j])) // stop if a contradiction is found
                        {
                            return;
                        }
                    }
                }
            }
        }

        public override void Display()
        {
            if (contradiction)
            {
                Console.Write("YES");
            }
            else
            {
                Console.Write("NO");
            }
        }
        public bool Contradict(string proposition1, string proposition2)
        {
            return (proposition1 == "~" + proposition2 || proposition2 == "~" + proposition1) && Kbase.Get(proposition1) is not Disjunction && Kbase.Get(proposition2) is not Disjunction;
        }
        public bool ApplyRule(string proposition1,string proposition2)
        {
            if(proposition1 != proposition2) // check if 2 propositions are not the same
            {
                if (Contradict(proposition1, proposition2)) // return true if a contradiction is found
                {
                    contradiction = true;
                    return true;
                }
                List<string> literals1 = new List<string>() { proposition1 };
                List<string> literals2 = new List<string>() { proposition2 };
                int complementary = 0;
                if (Kbase.Get(proposition1) is Disjunction) // if the proposition is a disjunction we get its subpropositions list
                {
                    literals1 = new List<string>(Kbase.Get(proposition1).SubPropositions);
                }
                if (Kbase.Get(proposition2) is Disjunction)
                {
                    literals2 = new List<string>(Kbase.Get(proposition2).SubPropositions);
                }
                foreach (string literal in new List<string>(literals1)) // compare all literals of one disjunction with all literal of the other disjunction
                {
                    if (literals2.Contains("~" + literal)) // if the other disjunction contain the negation of the current literal
                    {
                        literals1.Remove(literal);      // remove the complimentary pair
                        literals2.Remove("~" + literal);
                        complementary++;
                    }
                    else if (literal.Substring(0,1) == "~" && literals2.Contains(literal.TrimStart('~'))) // if this disjunction contain a negation of a literal in the other disjunction
                    {
                        literals1.Remove(literal);      // remove the complimentary pair
                        literals2.Remove(literal.TrimStart('~'));
                        complementary++;
                    }
                }
                literals1.AddRange(literals2); // get the remaining literals
                literals1.Sort();
                if (complementary == 1)    // a new fact is infered if there are 1 complimentary pair
                {
                    string disjunction = "";
                    foreach (string literal in literals1) // creating a new disjunction
                    {
                        if (!disjunction.Contains(literal))
                        {
                            if (disjunction != "")
                            {
                                disjunction += " || ";
                            }
                            disjunction += literal;
                        }
                    }
                    Kbase.AddFact(Kbase.Parse(disjunction)); // adding new fact
                }
            }
            return false;
        }
        public void ToCNF(string proposition)
        {
            List<string> literal = new List<string>();
            foreach (Proposition p in Kbase.Propositions)  // get all literals in the proposition
            {
                if (p is Literal && proposition.Contains(p.Name))
                {
                    literal.Add(p.Name);
                }
            }
            for (int i = 0; i < (1 << literal.Count); i++) // get all possible truth assignment combinations
            {
                string disjunction = "";
                Kbase.Facts.Clear();
                for (int j = 0; j < literal.Count; j++)
                {
                    if(disjunction != "")
                    {
                        disjunction += " || ";
                    }
                    if ((i & (1 << j)) != 0)  // use a binary couner method to determine which literals are true and which are false
                    {
                        disjunction += "~" + literal[j]; // false if 1
                        Kbase.AddFact(literal[j]);
                    }
                    else
                    {
                        disjunction += literal[j]; // true if 0
                    }
                }
                if (!Kbase.Get(proposition).IsTrue()) // choose the truth assignment set that make the proposition false
                {
                    clauses.Add(Kbase.Parse(disjunction));
                }
            }
        }
    }
}
