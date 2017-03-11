﻿using MahApps.Metro.Controls;
using System;
using System.Collections.Generic;
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
	/// updateHistoryData.xaml 的交互逻辑
	/// </summary>
	public partial class updateHistoryData : MetroWindow
	{
		[DllImport("DBLayer.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern void Delete(string sql);

		string tUserName;
		string tUserCount;
		string tUserPhone;
		string tShopName;
		string tMoney;
		string tCostMoney;
		string tDatetime;
		string updateHistoryDataUser = "UPDATE USERDATAHISTORY ";

		string HistoryDataTable = "UPDATE HISTORYDATA ";

		public updateHistoryData()
		{
			InitializeComponent();
		}
		

		private void updateHistoryData_Click(object sender, RoutedEventArgs e)
		{
			string temp = updateHistoryDataUser;
			temp += "SET ";

			temp += "USERNAME = '";
			temp += username.Text;
			temp += "' , ";

			temp += "USERCOUNT = '";
			temp += usercount.Text;
			temp += "' , ";

			temp += "USERPHONE = '";
			temp += userphone.Text;
			temp += "' , ";

			temp += "SHOPNAME = '";
			temp += shopName.Text;
			temp += "' , ";

			temp += "COSTMONEY = '";
			temp += usermoney.Text;
			temp += "', ";

			temp += "COSTMONEYFORUSER = '";
			temp += usercostMoney.Text;
			temp += "', ";

			temp += "DATETIME = '";
			temp += usertime.Text;

			temp += "' WHERE ";

			temp += "USERNAME = '";
			temp += tUserName;
			temp += "' and ";

			temp += "USERCOUNT = '";
			temp += tUserCount;
			temp += "' and ";

			temp += "USERPHONE = '";
			temp += tUserPhone;
			temp += "' and ";

			temp += "SHOPNAME = '";
			temp += tShopName;
			temp += "' and ";

			temp += "COSTMONEY = '";
			temp += tMoney;
			temp += "' and ";

			temp += "COSTMONEYFORUSER = '";
			temp += tCostMoney;
			temp += "' and ";

			temp += "DATETIME = '";
			temp += tDatetime;
			temp += "' ";
			Delete(temp);


            temp = HistoryDataTable;
			temp += "SET ";

			temp += "USERNAME = '";
			temp += username.Text;
			temp += "' , ";

			temp += "USERCOUNT = '";
			temp += usercount.Text;
			temp += "' , ";

			temp += "USERPHONE = '";
			temp += userphone.Text;
			temp += "' , ";

			temp += "SHOPNAME = '";
			temp += shopName.Text;
			temp += "' , ";

			temp += "COSTMONEY = '";
			temp += usermoney.Text;
			temp += "', ";

			temp += "COSTMONEYFORUSER = '";
			temp += usercostMoney.Text;
			temp += "', ";

			temp += "DATETIME = '";
			temp += usertime.Text;

			temp += "' WHERE ";

			temp += "USERNAME = '";
			temp += tUserName;
			temp += "' and ";

			temp += "USERCOUNT = '";
			temp += tUserCount;
			temp += "' and ";

			temp += "USERPHONE = '";
			temp += tUserPhone;
			temp += "' and ";

			temp += "SHOPNAME = '";
			temp += tShopName;
			temp += "' and ";

			temp += "COSTMONEY = '";
			temp += tMoney;
			temp += "' and ";

			temp += "COSTMONEYFORUSER = '";
			temp += tCostMoney;
			temp += "' and ";

			temp += "DATETIME = '";
			temp += tDatetime;
			temp += "' ";
			Delete(temp);


this.Close();
		}

		internal void SetLocalData(string name,string count, string phone,string shop,string money,string costmoney,string time)
		{
			tUserName = name;
			tUserCount = count;
			tShopName = shop;
			tUserPhone = phone;
			tMoney = money;
			tCostMoney = costmoney;
			tDatetime = time;

			username.Text = name;
			usercount.Text = count;
			shopName.Text = shop;
			userphone.Text = phone;
			usermoney.Text = money;
			usercostMoney.Text = costmoney;
			usertime.Text = time;
		}
	}
}
