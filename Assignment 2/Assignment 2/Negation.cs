using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class Negation : Proposition
    {
        public Negation(string name, Knowledge_Base kb) : base(name, kb)
        {
        }

        public override bool IsTrue()// true if its only subproposition is false
        {
            return !Kbase.Get(SubPropositions[0]).IsTrue();
        }
    }
}
