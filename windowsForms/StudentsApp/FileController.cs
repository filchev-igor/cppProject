using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace StudentsApp
{
    class FileController
    {
        private List<string> nameArray = new List<string>{"Harry","Ross",
                                 "Bruce","Cook",
                                 "Carolyn","Morgan",
                                 "Albert","Walker",
                                 "Randy","Reed",
                                 "Larry","Barnes",
                                 "Lois","Wilson",
                                 "Jesse","Campbell",
                                 "Ernest","Rogers",
                                 "Theresa","Patterson",
                                 "Henry","Simmons",
                                 "Michelle","Perry",
                                 "Frank","Butler",
                                 "Shirley", "Brooks",
                                  "Rachel","Edwards",
                                  "Christopher","Perez",
                                  "Thomas","Baker",
                                  "Sara","Moore",
                                  "Chris","Bailey",
                                  "Roger","Johnson",
                                  "Marilyn","Thompson",
                                  "Anthony","Evans",
                                  "Julie","Hall",
                                  "Paula","Phillips",
                                  "Annie","Hernandez",
                                  "Dorothy","Murphy",
                                  "Alice","Howard"};

        private List<string> surnameArray = new List<string>{
            "Ruth","Jackson", "Debra","Allen",
            "Gerald","Harris", "Raymond","Carter",
            "Jacqueline","Torres", "Joseph","Nelson",
                                "Carlos","Sanchez",
                                "Ralph","Clark",
                                "Jean","Alexander",
                                "Stephen","Roberts",
                                "Eric","Long",
                                "Amanda","Scott",
                                "Teresa","Diaz",
                                "Wanda","Thomas" };

        Random rnd = new Random();

        public void createFile(string fileName)
        {
            string path = fileName + ".txt";

            if (File.Exists(path))
                return;

            using (StreamWriter sw = File.CreateText(path))
            {
                sw.Write("Pavarde ");
                sw.Write("Vardas ");
                sw.Write("ND1 ");
                sw.Write("ND2 ");
                sw.Write("ND3 ");
                sw.Write("ND4 ");
                sw.Write("ND5 ");
                sw.Write("ND6 ");
                sw.Write("ND7 ");
                sw.Write("ND8 ");
                sw.Write("ND9 ");
                sw.Write("ND10 ");
                sw.Write("Egzaminas");
            }
        }

        public void fillFileWithRandomData(string fileName, int iterationsNumber)
        {
            Debug.WriteLine(iterationsNumber);

            string path = fileName + ".txt";

            if (!File.Exists(path))
                return;

            using (StreamWriter sw = File.AppendText(path))
            {
                for (int i = 0; i < iterationsNumber; i++)
                {
                    List<string> dataVector = new List<string>();

                    int randomNameKey = rnd.Next(0, nameArray.Count);
                    int randomSurnameKey = rnd.Next(0, surnameArray.Count);

                    dataVector.Add(nameArray[randomNameKey]);
                    dataVector.Add(surnameArray[randomSurnameKey]);

                    int homeworksNumber = rnd.Next(1, 10);

                    for (int j = 0; j < homeworksNumber; j++)
                    {
                        int mark = rnd.Next(1, 10);

                        dataVector.Add(mark.ToString());
                    }

                    for (int j = 0; j < 10 - homeworksNumber; j++)
                        dataVector.Add("-1");

                    int examMark = rnd.Next(1, 10);

                    dataVector.Add(examMark.ToString());

                    sw.WriteLine();

                    foreach (string s in dataVector)
                    {
                        string text = s + " ";

                        sw.Write(text);
                    }
                }
            }
        }
    }
}
