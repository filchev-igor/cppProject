using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudentsApp
{
    public partial class StartForm : Form
    {
        private string _fileName;
        private int _iterationsNumber = 100;
        private bool _isCalculatedByMean = true;

        public StartForm()
        {
            InitializeComponent();
        }

        private void disableButtons(Button activeButton = default)
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

        private void handleButton(string firstLabelText, string secondLabelText)
        {
            disableButtons();

            label2.Text = "Creating file...";

            FileController fileController = new FileController();

            fileController.createFile(_fileName);

            this._fileName = "";
            textBox1.Text = "";
            label2.Text = "File was created";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            disableButtons();

            label2.Text = "Creating file...";

            FileController fileController = new FileController();

            fileController.createFile(_fileName);

            this._fileName = "";
            textBox1.Text = "";
            textBox2.Text = "";
            label2.Text = "File was created";
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

        private void button3_Click(object sender, EventArgs e)
        {
            disableButtons();

            label2.Text = "Filling file with the data...";

            FileController fileController = new FileController();

            fileController.fillFileWithRandomData(_fileName, _iterationsNumber);

            this._fileName = "";
            textBox1.Text = "";
            textBox2.Text = "";
            label2.Text = "File was extended with the data";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            disableButtons();

            label2.Text = "Reading file, sorting and exporting. Please, wait a little bit...";

            FileController fileController = new FileController();

            fileController.dataSortExport(_fileName, _isCalculatedByMean);

            this._fileName = "";
            textBox1.Text = "";
            textBox2.Text = "";
            label2.Text = "Everything is done.";
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            int iterationsNumber = 0;

            Int32.TryParse(textBox2.Text, out iterationsNumber);

            this._iterationsNumber = iterationsNumber;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            button5.BackColor = Color.White;
            button4.BackColor = Color.Gainsboro;

            this._isCalculatedByMean = true;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            button4.BackColor = Color.White;
            button5.BackColor = Color.Gainsboro;

            this._isCalculatedByMean = false;
        }
    }
}
