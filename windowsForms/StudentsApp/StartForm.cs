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

        private void button1_Click(object sender, EventArgs e)
        {
            disableButtons();

            label1.Text = "Creating file...";

            FileController fileController = new FileController();

            fileController.createFile(_fileName);

            this._fileName = "";
            textBox1.Text = "";
            label1.Text = "File was created";
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
