USE [master]
GO

DROP TABLE PepsDB
GO

/****** Object:  Table [dbo].[Indices]    Script Date: 01/11/2014 15:22:27 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[PepsDB](
	[Date] [datetime] CONSTRAINT PK_PepsDB PRIMARY KEY NONCLUSTERED NOT NULL,
	[FTSE] [varchar](255) NULL,
	[S&P] [varchar](255) NULL,
	[NIKKEI] [varchar](255) NULL,
	[EUROSTOXX] [varchar](255) NULL,
	[Eur/JPY] [varchar](255) NULL,
	[Eur/USD] [varchar](255) NULL,
	[Eur/GBP] [varchar](255) NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO



--Check the content of the table.
SELECT PepsDB.*
FROM PepsDB
GO