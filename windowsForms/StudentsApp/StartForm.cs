using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudentsApp
{
    public partial class StartForm : Form
    {
        private string _fileName;

        public StartForm()
        {
            InitializeComponent();
        }

        private void disableButtons(Button activeButton)
        {
            if (activeButton != button1)
            {
                button1.Enabled = false;
                button1.BackColor = Color.Tomato;
            }

            if (activeButton != button2)
            {
                button2.Enabled = false;
                button2.BackColor = Color.Tomato;
            }

            if (activeButton != button3)
            {
                button3.Enabled = false;
                button3.BackColor = Color.Tomato;
            }
        }

        private void enableButtons()
        {
            button1.Enabled = true;
            button2.Enabled = true;
            button3.Enabled = true;

            button1.BackColor = Color.SteelBlue;
            button2.BackColor = Color.SteelBlue;
            button3.BackColor = Color.SteelBlue;
        }

        private void createFile(string fileName)
        {

            std::ofstream fileOut;

            fileOut.open(fileName, ios_base::in);

            if (fileOut)
                return;

            fileOut.open(fileName, ios_base::app);

            fileOut << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 ND6 ND7 ND8 ND9 ND10 Egzaminas" << endl;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string fileName = _fileName;

            disableButtons(button1);

            this._fileName = "";
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            string fileName = textBox1.Text.Trim();

            if (fileName.Length < 1)
            {
                disableButtons();

                return;
            }

            enableButtons();

            this._fileName = fileName;
        }
    }
}
