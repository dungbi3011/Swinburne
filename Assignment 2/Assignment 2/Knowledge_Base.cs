using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml.Linq;
using static System.Net.Mime.MediaTypeNames;

namespace Assignment2
{
    public class Knowledge_Base
    {
        List<Proposition> propositions = new List<Proposition>();
        List<string> kb = new List<string>();
        List<string> facts = new List<string>();
        string goal;

        public void Setup(string[] propositions, string sentence)
        {
            foreach (string proposition in propositions) // build the KB
            {
                if(proposition != "")
                {
                    AddKB(Parse(proposition));
                }
            }
            goal = Parse(sentence); // set the goal/sentence
        }

        
        public string BreakParentheses(string proposition, bool full) // get the part of the string that are not eclosed by brackets
        {
            string replaced = Regex.Replace(proposition, @"\([^()]*\)", "[]");
            if (replaced == "[]" && !full)
            {
                return proposition;
            }
            if (replaced == proposition)
            {
                return replaced;
            }
            return BreakParentheses(replaced, full);
        }
        public string Parse(string proposition) // parse a string to a proposition
        {
            proposition = proposition.Trim();                                        //preprocess the input string
            if (proposition.Count(c => c == '(') > proposition.Count(c => c == ')'))  // remove invalid brackets
            {
                proposition = proposition.Substring(1);
            }  
            else if (proposition.Count(c => c == '(') < proposition.Count(c => c == ')'))
            {
                proposition = proposition.Substring(0, proposition.Length - 1);
            }
            while(BreakParentheses(proposition, true) == "[]")      // remove unnecessary brackets
            {
                proposition = proposition.Substring(1, proposition.Length - 2);
            }
            if (proposition != "" && Get(proposition) == null)
            {
                string[] subpropositions = new string[0];
                string breakeparentheses = BreakParentheses(proposition, false); // get the part outside of brackets
                string separator = "";
                if (proposition.Substring(0,1) == "~" && (!(proposition.Contains("<=>") || proposition.Contains("=>") || proposition.Contains("&") || proposition.Contains("||")) || BreakParentheses(proposition, true).TrimStart('~') == "[]"))
                {                                                     //proposition is a naegation
                    propositions.Add(new Negation(proposition, this));
                    subpropositions = new string[] { proposition.Substring(1, proposition.Length - 1) };
                }
                else if (breakeparentheses.Split("<=>").Length == 2)  // proposition is a bicondition
                {
                    propositions.Add(new Biconditions(proposition, this));
                    separator = "<=>";                                
                }
                else if (breakeparentheses.Split("=>").Length == 2) // proposition is an implication
                {
                    propositions.Add(new Implication(proposition, this));
                    separator = "=>";
                }
                else if (breakeparentheses.Split("= >").Length == 2)
                {
                    propositions.Add(new Implication(proposition, this));
                    separator = "= >";
                }
                else if (breakeparentheses.Split("||").Length >= 2) // proposition is a disjunction
                {
                    propositions.Add(new Disjunction(proposition, this));
                    separator = "||";
                }
                else if (breakeparentheses.Split("&").Length >= 2) // proposition is a conjunction
                {
                    propositions.Add(new Conjunction(proposition, this));
                    separator = "&";
                }
                else                                              // proposition is a literal
                {
                    propositions.Add(new Literal(proposition, this));
                }
                if(separator != "")
                {
                    string p = proposition;
                    foreach (string s in breakeparentheses.Split("[]")) // replace the separator that are outside of brackets with *
                    {
                        if (s != "")
                        {
                            p = p.Replace(s, s.Replace(separator, "*"));
                        }
                    }
                    subpropositions = p.Split("*");  // split the proposition into sub propositions
                } 
                foreach(string subproposition in subpropositions) // repeat the process for subpropositions
                {
                    Get(proposition).SubPropositions.Add(Parse(subproposition)); // recursion
                }
            }
            return proposition;
        }


        public Proposition Get(string name) // get a proposition by name
        {
            foreach(var implication in propositions)
            {
                if(implication.Name == name)
                {
                    return implication;
                }
            }
            //Console.WriteLine("NULL: " +  name);
            return null;
        }

        public bool IsFact(string name) // check if a proposition is a fact
        {
            return facts.Contains(name);
        }
        public bool InKB(string name) // check if a proposition is part of KB
        {
            return kb.Contains(name);
        }

        public void AddFact(string fact) // add a proposition to facts
        {
            if (!facts.Contains(fact) && fact != "")
            {
                facts.Add(fact);
            }
        }

        public void AddKB(string k) // make a proposition part of KB
        {
            if (!kb.Contains(k) && k != "")
            {
                kb.Add(k);
            }
        }

        public List<Proposition> Propositions { get { return propositions; } }

        public List<string> Facts { get { return facts; } }
        public List<string> KB { get { return kb; } }

        public string Goal { get { return goal; } set { goal = value; } }
    }
}
