using MahApps.Metro.Controls;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;
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

namespace 刷单管理
{
    /// <summary>
    /// AddUser.xaml 的交互逻辑
    /// </summary>
    public partial class AddUser : MetroWindow
    {
        string cmdInsert = "INSERT INTO USERINFO (USERNAME , USERCOUNT , USERPHONE ) VALUES ";
        string cmdInsertShop = "INSERT INTO SHOPINFO (USERNAME , USERCOUNT , USERPHONE ) VALUES ";
        string cmdDelete = "delete from USERINFO where ";
        string cmdDeleteShop = "delete from SHOPINFO where ";


        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Init();

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Fini();

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Select(string sql);

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Insert(string sql);

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void Delete(string sql);

        [DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern void GetMsg(StringBuilder userName, StringBuilder userCount, StringBuilder userPhone);

        class CInfoList
        {
            public CInfoList(string sUserName,
            string sUserCount,
            string sUserPhone)
            {
                UserName = sUserName;
                UserCount = sUserCount;
                UserPhone = sUserPhone;
            }
            public string UserName { get; set; }
            public string UserCount { get; set; }
            public string UserPhone { get; set; }
        }

        MangerMoney m_manger;
        private ObservableCollection<CInfoList> Users = new ObservableCollection<CInfoList>();
        public AddUser(MangerMoney mangerMoney)
        {
            m_manger = mangerMoney;
            InitializeComponent();

            ListCollectionView cs = new ListCollectionView(Users);
            infoList.ItemsSource = cs;

            Users.Clear();
            Select(m_manger.sql);
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
                    Users.Add(new CInfoList(TuserName.ToString(), TuserCount.ToString(), TuserPhone.ToString()));
                }
            }
            while (Name.Equals("") == false);
        }

        private void backMainWindows_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            m_manger.Show();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            this.Close();
            m_manger.Show();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            object o = infoList.SelectedItem;
            if (o == null)
                return;
            CInfoList item = o as CInfoList;
            string sql = "";
			if (chooseUserOrShop.SelectionBoxItem.Equals("用户"))
			{
				sql = cmdDelete;
			}
			if (chooseUserOrShop.SelectionBoxItem.Equals("商户"))
			{
				sql = cmdDeleteShop;
			}

            if (!item.UserName.Equals(""))
            {
                sql += "USERNAME = '";
                sql += item.UserName.ToString();
                sql += "'";
                if (!item.UserCount.Equals(""))
                {
                    sql += " and ";
                    sql += "USERCOUNT='";
                    sql += item.UserCount.ToString();
                    sql += "'";
                    if (!item.UserPhone.Equals(""))
                    {
                        sql += " and ";
                        sql += " USERPHONE = '";
                        sql += item.UserPhone.ToString();
                        sql += "' ";
                    }
                }
                Delete(sql);
            }
            Users.Remove(item);
            m_manger.Update();
        }

        private void sqlAdd_Click(object sender, RoutedEventArgs e)
        {
            if (!userName.Text.Equals("") && !userCount.Text.Equals(""))
            {
                string sql = cmdInsert;
                sql += "('";
                sql += userName.Text;
                sql += " ','";
                sql += userCount.Text;
                sql += " ','";
                sql += userPhone.Text;
                sql += " ')";
                Insert(sql);
            }
            m_manger.Update();

            Users.Clear();
            Select(m_manger.sql);
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
                    Users.Add(new CInfoList(TuserName.ToString(), TuserCount.ToString(), TuserPhone.ToString()));
                }
            }
            while (Name.Equals("") == false);
        }

		private void AddShop_Click(object sender, RoutedEventArgs e)
		{
            if (!userName.Text.Equals("") && !userCount.Text.Equals(""))
            {
                string sql = cmdInsertShop;
                sql += "('";
                sql += userName.Text;
                sql += " ','";
                sql += userCount.Text;
                sql += " ','";
                sql += userPhone.Text;
                sql += " ')";
                Insert(sql);
            }
            m_manger.Update();

            Users.Clear();
            Select(m_manger.sqlShop);
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
                    Users.Add(new CInfoList(TuserName.ToString(), TuserCount.ToString(), TuserPhone.ToString()));
                }
            }
            while (Name.Equals("") == false);
		}

		private void AddToDb_Click(object sender, RoutedEventArgs e)
		{
			if(chooseUserOrShop.SelectionBoxItem.Equals("用户"))
			{
				sqlAdd_Click(sender,e);
			}
			if (chooseUserOrShop.SelectionBoxItem.Equals("商户"))
			{
				AddShop_Click(sender,e);
			}
		}

		private void search_Click(object sender, RoutedEventArgs e)
		{
			string selectSql = "";
			if(chooseUserOrShop.SelectionBoxItem.Equals("用户"))
			{
				selectSql = m_manger.sql;
			}
			if (chooseUserOrShop.SelectionBoxItem.Equals("商户"))
			{
				selectSql = m_manger.sqlShop;
			}

			m_manger.Update();

            Users.Clear();
            Select(selectSql);
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
                    Users.Add(new CInfoList(TuserName.ToString(), TuserCount.ToString(), TuserPhone.ToString()));
                }
            }
            while (Name.Equals("") == false);

		}
    }
}
