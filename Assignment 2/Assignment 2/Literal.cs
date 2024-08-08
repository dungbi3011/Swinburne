using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class Literal : Proposition
    {
        public Literal(string name, Knowledge_Base kb) : base(name, kb)
        {
        }

        public override bool IsTrue() // true if it is a fact
        {
            return Kbase.IsFact(Name);
        }

    }
}
