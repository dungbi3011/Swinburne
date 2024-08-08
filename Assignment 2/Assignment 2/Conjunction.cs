using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class Conjunction : Proposition
    {
        public Conjunction(string name, Knowledge_Base kb) : base(name,kb)
        {
        }

        public override bool IsTrue() // true if all subpropositions are true
        {
            foreach (string p in SubPropositions)
            {
                if (!Kbase.Get(p).IsTrue())
                {
                    return false;
                }
            }
            return true;
        }

        public override void Infer() // if a conjunction is true that mean all of its subpropositions is also true
        {
            foreach(string p in SubPropositions)
            {
                Kbase.AddFact(p);
            }
        }
    }
}
