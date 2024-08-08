using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class Biconditions : Proposition
    {
        public Biconditions(string name, Knowledge_Base kb) : base(name, kb)
        {
        }

        public override bool IsTrue() // true if both subpropositions are true or both subpropositions are false
        {
            return Kbase.Get(SubPropositions[0]).IsTrue() == Kbase.Get(SubPropositions[1]).IsTrue();
        }

        public override void Infer() // if 1 clause of the bicondition is true then the other is also true
        {
            if (Kbase.IsFact(SubPropositions[0]))
            {
                Kbase.AddFact(SubPropositions[1]);
            }
            else if (Kbase.IsFact(SubPropositions[1]))
            {
                Kbase.AddFact(SubPropositions[0]);
            }
        }
    }
}
