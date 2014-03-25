USE [master]
GO


DROP TABLE dbo.Component
GO

/****** Object:  Table [dbo].[Indices]    Script Date: 01/11/2014 15:22:27 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Component](
	[Date][varchar](255) CONSTRAINT PK_Component PRIMARY KEY NONCLUSTERED NOT NULL,
	[ValLiquidative] [varchar](255) NULL,
	[PartFTSE] [varchar](255) NULL,
	[PartS&P] [varchar](255) NULL,
	[PartNikkei] [varchar](255) NULL,
	[PartEuro] [varchar](255) NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO
select * from Component


