﻿#pragma warning disable 1591
//------------------------------------------------------------------------------
// <auto-generated>
//     Ce code a été généré par un outil.
//     Version du runtime :4.0.30319.18449
//
//     Les modifications apportées à ce fichier peuvent provoquer un comportement incorrect et seront perdues si
//     le code est régénéré.
// </auto-generated>
//------------------------------------------------------------------------------

namespace AffichageBD
{
	using System.Data.Linq;
	using System.Data.Linq.Mapping;
	using System.Data;
	using System.Collections.Generic;
	using System.Reflection;
	using System.Linq;
	using System.Linq.Expressions;
	using System.ComponentModel;
	using System;
	
	
	[global::System.Data.Linq.Mapping.DatabaseAttribute(Name="master")]
	public partial class PepsDBDataContext : System.Data.Linq.DataContext
	{
		
		private static System.Data.Linq.Mapping.MappingSource mappingSource = new AttributeMappingSource();
		
    #region Définitions de méthodes d'extensibilité
    partial void OnCreated();
    partial void InsertComponent(Component instance);
    partial void UpdateComponent(Component instance);
    partial void DeleteComponent(Component instance);
    #endregion
		
		public PepsDBDataContext() : 
				base(global::AffichageBD.Properties.Settings.Default.masterConnectionString, mappingSource)
		{
			OnCreated();
		}
		
		public PepsDBDataContext(string connection) : 
				base(connection, mappingSource)
		{
			OnCreated();
		}
		
		public PepsDBDataContext(System.Data.IDbConnection connection) : 
				base(connection, mappingSource)
		{
			OnCreated();
		}
		
		public PepsDBDataContext(string connection, System.Data.Linq.Mapping.MappingSource mappingSource) : 
				base(connection, mappingSource)
		{
			OnCreated();
		}
		
		public PepsDBDataContext(System.Data.IDbConnection connection, System.Data.Linq.Mapping.MappingSource mappingSource) : 
				base(connection, mappingSource)
		{
			OnCreated();
		}
		
		public System.Data.Linq.Table<Component> Component
		{
			get
			{
				return this.GetTable<Component>();
			}
		}
		
		public System.Data.Linq.Table<PepsDB> PepsDB
		{
			get
			{
				return this.GetTable<PepsDB>();
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.TableAttribute(Name="dbo.Component")]
	public partial class Component : INotifyPropertyChanging, INotifyPropertyChanged
	{
		
		private static PropertyChangingEventArgs emptyChangingEventArgs = new PropertyChangingEventArgs(String.Empty);
		
		private string _Date;
		
		private string _ValLiquidative;
		
		private string _PartFTSE;
		
		private string _PartS_P;
		
		private string _PartNikkei;
		
		private string _PartEuro;
		
    #region Définitions de méthodes d'extensibilité
    partial void OnLoaded();
    partial void OnValidate(System.Data.Linq.ChangeAction action);
    partial void OnCreated();
    partial void OnDateChanging(string value);
    partial void OnDateChanged();
    partial void OnValLiquidativeChanging(string value);
    partial void OnValLiquidativeChanged();
    partial void OnPartFTSEChanging(string value);
    partial void OnPartFTSEChanged();
    partial void OnPartS_PChanging(string value);
    partial void OnPartS_PChanged();
    partial void OnPartNikkeiChanging(string value);
    partial void OnPartNikkeiChanged();
    partial void OnPartEuroChanging(string value);
    partial void OnPartEuroChanged();
    #endregion
		
		public Component()
		{
			OnCreated();
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_Date", DbType="VarChar(255) NOT NULL", CanBeNull=false, IsPrimaryKey=true)]
		public string Date
		{
			get
			{
				return this._Date;
			}
			set
			{
				if ((this._Date != value))
				{
					this.OnDateChanging(value);
					this.SendPropertyChanging();
					this._Date = value;
					this.SendPropertyChanged("Date");
					this.OnDateChanged();
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_ValLiquidative", DbType="VarChar(255)")]
		public string ValLiquidative
		{
			get
			{
				return this._ValLiquidative;
			}
			set
			{
				if ((this._ValLiquidative != value))
				{
					this.OnValLiquidativeChanging(value);
					this.SendPropertyChanging();
					this._ValLiquidative = value;
					this.SendPropertyChanged("ValLiquidative");
					this.OnValLiquidativeChanged();
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_PartFTSE", DbType="VarChar(255)")]
		public string PartFTSE
		{
			get
			{
				return this._PartFTSE;
			}
			set
			{
				if ((this._PartFTSE != value))
				{
					this.OnPartFTSEChanging(value);
					this.SendPropertyChanging();
					this._PartFTSE = value;
					this.SendPropertyChanged("PartFTSE");
					this.OnPartFTSEChanged();
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Name="[PartS&P]", Storage="_PartS_P", DbType="VarChar(255)")]
		public string PartS_P
		{
			get
			{
				return this._PartS_P;
			}
			set
			{
				if ((this._PartS_P != value))
				{
					this.OnPartS_PChanging(value);
					this.SendPropertyChanging();
					this._PartS_P = value;
					this.SendPropertyChanged("PartS_P");
					this.OnPartS_PChanged();
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_PartNikkei", DbType="VarChar(255)")]
		public string PartNikkei
		{
			get
			{
				return this._PartNikkei;
			}
			set
			{
				if ((this._PartNikkei != value))
				{
					this.OnPartNikkeiChanging(value);
					this.SendPropertyChanging();
					this._PartNikkei = value;
					this.SendPropertyChanged("PartNikkei");
					this.OnPartNikkeiChanged();
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_PartEuro", DbType="VarChar(255)")]
		public string PartEuro
		{
			get
			{
				return this._PartEuro;
			}
			set
			{
				if ((this._PartEuro != value))
				{
					this.OnPartEuroChanging(value);
					this.SendPropertyChanging();
					this._PartEuro = value;
					this.SendPropertyChanged("PartEuro");
					this.OnPartEuroChanged();
				}
			}
		}
		
		public event PropertyChangingEventHandler PropertyChanging;
		
		public event PropertyChangedEventHandler PropertyChanged;
		
		protected virtual void SendPropertyChanging()
		{
			if ((this.PropertyChanging != null))
			{
				this.PropertyChanging(this, emptyChangingEventArgs);
			}
		}
		
		protected virtual void SendPropertyChanged(String propertyName)
		{
			if ((this.PropertyChanged != null))
			{
				this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
			}
		}
	}
	
	[global::System.Data.Linq.Mapping.TableAttribute(Name="dbo.PepsDB")]
	public partial class PepsDB
	{
		
		private string _Actif;
		
		private string _Date;
		
		private string _High;
		
		private string _Low;
		
		private string _Open;
		
		private string _Close;
		
		public PepsDB()
		{
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_Actif", DbType="VarChar(255)")]
		public string Actif
		{
			get
			{
				return this._Actif;
			}
			set
			{
				if ((this._Actif != value))
				{
					this._Actif = value;
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_Date", DbType="VarChar(255)")]
		public string Date
		{
			get
			{
				return this._Date;
			}
			set
			{
				if ((this._Date != value))
				{
					this._Date = value;
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_High", DbType="VarChar(255)")]
		public string High
		{
			get
			{
				return this._High;
			}
			set
			{
				if ((this._High != value))
				{
					this._High = value;
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Storage="_Low", DbType="VarChar(255)")]
		public string Low
		{
			get
			{
				return this._Low;
			}
			set
			{
				if ((this._Low != value))
				{
					this._Low = value;
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Name="[Open]", Storage="_Open", DbType="VarChar(255)")]
		public string Open
		{
			get
			{
				return this._Open;
			}
			set
			{
				if ((this._Open != value))
				{
					this._Open = value;
				}
			}
		}
		
		[global::System.Data.Linq.Mapping.ColumnAttribute(Name="[Close]", Storage="_Close", DbType="VarChar(255)")]
		public string Close
		{
			get
			{
				return this._Close;
			}
			set
			{
				if ((this._Close != value))
				{
					this._Close = value;
				}
			}
		}
	}
}
#pragma warning restore 1591
