using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Shapes;
using MahApps.Metro.Controls;
using System.Runtime.InteropServices;

namespace 刷单管理
{
    /// <summary>
    /// MangerMoney.xaml 的交互逻辑
    /// </summary>
    public partial class MangerMoney : MetroWindow
    {
        public string sql = "select * from USERINFO ";
        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Init();

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Fini();

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Select(string sql);

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void GetMsg(StringBuilder userName, StringBuilder userCount, StringBuilder userPhone);
        private ObservableCollection<CInfoList> Users = new ObservableCollection<CInfoList>();
        class CInfoList
        {
            public CInfoList(string sUserName,
            string sUserCount,
            string sUserPhone ,
            string sShopName ,
            string sCostMoney ,
            string sCostForUser)
            {
                UserName = sUserName;
                UserCount = sUserCount;
                UserPhone = sUserPhone;
                ShopName = sShopName;
                CostMoney = sCostMoney;
                CostForUser = sCostForUser;
            }
            public string UserName { get; set; }
            public string UserCount { get; set; }
            public string UserPhone { get; set; }
            public string ShopName { get; set; }
            public string CostMoney{ get; set; }
            public string CostForUser{ get; set; }
        }
        public MangerMoney()
        {
            InitializeComponent();
            ListCollectionView cs = new ListCollectionView(Users);
            infoList.ItemsSource = cs;

            //从数据库中读入用户信息
            Init();

            userName.Items.Clear();
            Select(sql);
            System.Threading.Thread.Sleep(100);
            string Name = "";

            do
            {
                StringBuilder TuserName = new StringBuilder(2048);
                StringBuilder TuserCount = new StringBuilder(2048);
                StringBuilder TuserPhone = new StringBuilder(2048);
                GetMsg(TuserName, TuserCount, TuserPhone);
                Name = TuserName.ToString();
                if(Name.Equals("") == false)
                {
                    ComboBoxItem comboxIten = new ComboBoxItem();
                    comboxIten.Content = Name;
                    userName.Items.Add(comboxIten);
                }
            }
            while (Name.Equals("") == false);
            userName.SelectedIndex = -1;

        }
        public void Update()
        {
            userCount.Clear();
            userPhone.Clear();
            userName.Items.Clear();
            Select(sql);
            System.Threading.Thread.Sleep(100);
            string Name = "";
            do
            {
                StringBuilder TuserName = new StringBuilder(2048);
                StringBuilder TuserCount = new StringBuilder(2048);
                StringBuilder TuserPhone = new StringBuilder(2048);
                GetMsg(TuserName, TuserCount, TuserPhone);
                Name = TuserName.ToString();
                if (Name.Equals("") == false)
                {
                    ComboBoxItem comboxIten = new ComboBoxItem();
                    comboxIten.Content = Name;
                    userName.Items.Add(comboxIten);
                }
            }
            while (Name.Equals("") == false);
            userName.SelectedIndex = -1;
        }
        public class Person
        {
            public string Name { get; set; }
            public int Age { get; set; }
        }
        private void addItem_Click(object sender, RoutedEventArgs e)
        {
            string sUserName = userName.Text;
            string sUserCount = userCount.Text;
            string sUserPhone = userPhone.Text;
            string sShopName = shopName.Text;
            string sCostMoney = costMoney.Text.ToString();
            string sCostForUser = costForUser.Text.ToString();
            Users.Add(new CInfoList(sUserName, sUserCount, sUserPhone, sShopName, sCostMoney, sCostForUser));
        }
       
        
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            object o = infoList.SelectedItem;
            if (o == null)
                return;
            CInfoList item = o as CInfoList;
            Users.Remove(item);
        }

        private void calcMoney_Click(object sender, RoutedEventArgs e)
        {
            int AllMoney  = 0;
            if (!countMoney.Text.Equals(""))
            {
                AllMoney = Int32.Parse(countMoney.Text);
            }
            else
            {
                MessageBox.Show("输入金额");
            }
            int CostMoney = 0;
            for (int i = 0; i < Users.Count;i++ )
            {
                if (!Users[i].CostMoney.Equals(""))
                {
                    CostMoney += Int32.Parse(Users[i].CostMoney.ToString());
                }
                if (!Users[i].CostForUser.Equals(""))
                {
                    CostMoney += Int32.Parse(Users[i].CostForUser.ToString());
                }

            }
            int income = AllMoney - CostMoney;
            incomeMoney.Text = income.ToString();
        }


        private void userName_Selected(object sender, RoutedEventArgs e)
        {
            ComboBoxItem combox = (ComboBoxItem)sender;

            string test = combox.Content.ToString();
            MessageBox.Show(test);
            return;
        }

        private void shopName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox combox = (ComboBox)sender;
            ComboBoxItem item = combox.SelectedItem as ComboBoxItem;
            if (item != null)
            {
                //MessageBox.Show(item.Content.ToString());
            }
        }

        private void userName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox combox = (ComboBox)sender;
            ComboBoxItem item = combox.SelectedItem as ComboBoxItem;
            
            if (item != null)
            {
                //MessageBox.Show(item.Content.ToString());
                string searchUser = sql + "where USERNAME = " + "'" + item.Content.ToString() + "'";
                Select(searchUser);

                string Name = "";
                StringBuilder TuserName = new StringBuilder(2048);
                StringBuilder TuserCount = new StringBuilder(2048);
                StringBuilder TuserPhone = new StringBuilder(2048);
                GetMsg(TuserName, TuserCount, TuserPhone);
                Name = TuserName.ToString();

                if (Name.Equals("") == false)
                {
                    userCount.Text = TuserCount.ToString();
                    userPhone.Text = TuserPhone.ToString();
                }
                else
                {
                    userCount.Clear();
                    userPhone.Clear();
                }
            }
        }

        private void addUser_Click(object sender, RoutedEventArgs e)
        {
            AddUser addUser = new AddUser(this);
            this.Visibility = (Visibility)1;
            addUser.Show();
        }
    }
}
