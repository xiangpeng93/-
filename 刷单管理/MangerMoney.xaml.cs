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

namespace 刷单管理
{
    /// <summary>
    /// MangerMoney.xaml 的交互逻辑
    /// </summary>
    public partial class MangerMoney : MetroWindow
    {
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
                    CostMoney += Int32.Parse(Users[i].CostForUser.ToString());
                }
            }
            int income = AllMoney - CostMoney;
            incomeMoney.Text = income.ToString();
        }
    }
}
