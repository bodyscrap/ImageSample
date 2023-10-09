using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ImageUtil;

namespace ImageSample
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool IsBusy = true;
        MovieClient? client = null;
        public MainWindow()
        {
            InitializeComponent();
        }
        public void OnCapture(MovieClient hClient)
        {
            if(IsBusy) return;
            IsBusy = true;
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                image.Source = hClient.GetFrame().CreateBitmapSoruce();
                IsBusy = false;
            }));
        }

        private void StopClient()
        {
            if (client != null)
            {
                client.OnCapture -= OnCapture;
                client.Stop();
                client = null;
                IsBusy = true;
            }
        }
        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            StopClient();
            String path = textBox.Text;
            client = new MovieClient(path);
            client.OnCapture += OnCapture;
            IsBusy = false;
            client.Start();

        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            StopClient();
        }
    }
}
