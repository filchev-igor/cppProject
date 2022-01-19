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

        private Random rnd = new Random();

        private const string RESULT_MARK_MEAN_LT = "Galutinis (Vid.)";
        private const string RESULT_MARK_MEDIAN_LT = "Galutinis (Med.)";

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

        private double calculateFinalMark(List<double> homeworkMarksArray, double examMark, bool isCalculatedByMean)
        {
            double homeworksMarkResult = 0;

            if (isCalculatedByMean)
            {
                foreach (double mark in homeworkMarksArray)
                    homeworksMarkResult += mark;

                homeworksMarkResult /= Convert.ToDouble(homeworkMarksArray.Count);
            }
            else
            {
                int arrayLength = homeworkMarksArray.Count;

                if (arrayLength % 2 == 1)
                {
                    int position = (arrayLength + 1) / 2;

                    homeworksMarkResult = homeworkMarksArray[position];
                }
                else
                {
                    int position = arrayLength / 2;

                    homeworksMarkResult = (homeworkMarksArray[position] + homeworkMarksArray[position + 1]) / 2;

                }
            }

            return 0.4 * homeworksMarkResult + 0.6 * examMark;
        }

        public void dataSortExport(string fileName, bool isCalculatedByMean)
        {
            List<List<string>> data = new List<List<string>>();
            List<List<string>> modifiedData = new List<List<string>>();
            List<List<string>> passedStudentsList = new List<List<string>>();
            List<List<string>> failedStudentsList = new List<List<string>>();

            string path = fileName + ".txt";

            if (!File.Exists(path))
                return;

            using (StreamReader sr = File.OpenText(path))
            {
                string line = "";
                
                while ((line = sr.ReadLine()) != null)
                {
                    List<string> sList = new List<string>();

                    foreach (string s in line.Split(' '))
                        sList.Add(s);

                    data.Add(sList);
                }
            }

            foreach (List<string> array in data) {
                if (array[0] == "Pavarde")
                    continue;

                List<string> lineArray = new List<string>();
                List<double> homeworkMarksArray = new List<double>();

                lineArray.Add(array[0]);
                lineArray.Add(array[1]);

                for (int i = 2; i < array.Count - 1; i++)
                {
                    double mark = Convert.ToDouble(array[i]);

                    if (mark < 0)
                        continue;

                    homeworkMarksArray.Add(mark);
                }

                //2 instead of 1 due to existing empty space after last item
                double examMark = Convert.ToDouble(array[array.Count - 2]);
                double finalMark = calculateFinalMark(homeworkMarksArray, examMark, isCalculatedByMean);

                array.Add(finalMark.ToString());

                modifiedData.Add(array);
            }

            modifiedData.Sort((a, b) => b[2].CompareTo(a[2]));

            foreach (List<string> array in modifiedData)
            {
                List<string> newArray = new List<string>();

                double mark = Convert.ToDouble(array[2]);

                newArray.Add(array[0]);
                newArray.Add(array[1]);
                newArray.Add(array[2]);

                if (mark >= 5)
                    passedStudentsList.Add(newArray);
                else
                    failedStudentsList.Add(newArray);
            }

            List<string> headerArray = new List<string>();

            headerArray.Add(data[0][0]);
            headerArray.Add(data[0][1]);
            headerArray.Add(isCalculatedByMean ? RESULT_MARK_MEAN_LT : RESULT_MARK_MEDIAN_LT);

            passedStudentsList.Insert(0, headerArray);
            failedStudentsList.Insert(0, headerArray);

            string passedStudentsPath = fileName + "_passed_students.txt";
            string failedStudentsPath = fileName + "_failed_students.txt";

            using (StreamWriter sw = File.AppendText(passedStudentsPath))
            {
                foreach (List<string> array in passedStudentsList)
                {
                    foreach (string s in array)
                    {
                        string text = s + " ";

                        sw.Write(text);
                    }
                        

                    sw.WriteLine();
                }
            }

            using (StreamWriter sw = File.AppendText(failedStudentsPath))
            {
                foreach (List<string> array in failedStudentsList)
                {
                    foreach (string s in array)
                    {
                        string text = s + " ";

                        sw.Write(text);
                    }

                    sw.WriteLine();
                }
            }
        }
    }
}
