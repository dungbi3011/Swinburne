using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class Disjunction : Proposition
    {
        public Disjunction(string name, Knowledge_Base kb) : base(name, kb)
        {
        }

        public override bool IsTrue()// true if at least 1 subproposition is true
        {
            foreach (string p in SubPropositions)
            {
                if (Kbase.Get(p).IsTrue())
                {
                    return true;
                }
            }
            return false;
        }
    }
}
