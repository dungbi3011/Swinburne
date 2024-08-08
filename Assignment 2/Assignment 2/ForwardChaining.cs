using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class ForwardChaining : Method
    {
        public ForwardChaining(Knowledge_Base kb) : base(kb) { }
        public override void Run(string query)
        {
            int factcount = -1;
            while (factcount < Kbase.Facts.Count) // stop if no new fact is derived in the previous iteration
            {
                factcount = Kbase.Facts.Count;
                foreach (string proposition in Kbase.KB) // run Infer for all propositions in the KB
                {
                    Kbase.Get(proposition).Infer();
                    if (Kbase.Get(proposition) is Literal) // add literal to facts if they are part of the KB
                    {
                        Kbase.AddFact(proposition);
                    }
                    if (Kbase.IsFact(query)) // stop if the goal is proven
                    {
                        return;
                    }
                }
            }
        }
    }
}
