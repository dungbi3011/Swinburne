namespace Assignment2
{
    public abstract class Proposition
    {
        Knowledge_Base kb;
        public Proposition(string name, Knowledge_Base kb)
        {
            this.name = name;
            this.kb = kb;
        }
        string name;
        List<string> subpropositions = new List<string>();

        public abstract bool IsTrue(); // check if the proposition is true, this will be overriden by children classes


        public virtual void Infer() // some proposition type like implication can infer new fact
        {
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public List<string> SubPropositions
        {
            get { return subpropositions; }
            set { subpropositions = value; }
        }
        public Knowledge_Base Kbase { get { return kb; } }
    }
}
