using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace Assignment2
{
    public class BackwardChaining : Method
    {
        List<string> visited = new List<string>();
        public BackwardChaining(Knowledge_Base kb) : base(kb) { }
        public override void Run(string query)
        {
            if (Kbase.Get(query) != null && !visited.Contains(query)) // check if proposition exist
            {
                visited.Add(query);
                foreach (string kb in Kbase.KB) 
                {
                    Proposition proposition = Kbase.Get(kb);
                    if (proposition.SubPropositions.Count == 2 && proposition is Implication) // get all implication in KB
                    {
                        if (proposition.SubPropositions[1] == query) // find implication where the current proposition is the consequent
                        {
                            Run(proposition.SubPropositions[0]); // recursively try to prove the antecedent
                            proposition.Infer();
                        }
                    }
                }
                foreach (string subproposition in Kbase.Get(query).SubPropositions)
                {
                    Run(subproposition); // recursively try to prove its subpropositions
                }
                if(Kbase.InKB(query)) // add literal to facts if they are part of the KB
                {
                    Kbase.AddFact(query);
                }
            }
        }
    }
}
