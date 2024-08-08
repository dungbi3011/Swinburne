using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment2
{
    public class Implication : Proposition
    {
        public Implication(string name, Knowledge_Base kb) : base(name, kb)
        {
        }

        public override bool IsTrue()// only false if the antecedent is true and the consequent is false
        {
            return !(Kbase.Get(SubPropositions[0]).IsTrue() && !Kbase.Get(SubPropositions[1]).IsTrue());
        }

        public override void Infer()// if the antecedent is true then the consequent is true
        {
            if (Kbase.Get(SubPropositions[0]).IsTrue())
            {
                Kbase.AddFact(SubPropositions[1]);
            }
        }
    }
}
