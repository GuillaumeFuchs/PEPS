USE [master]
GO


DROP TABLE dbo.InfoProd
GO

/****** Object:  Table [dbo].[Indices]    Script Date: 01/11/2014 15:22:27 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[InfoProd](
	[NomProd][varchar](255) CONSTRAINT PK_InfoProd PRIMARY KEY NONCLUSTERED NOT NULL,
	[NbPartAchetes] [varchar](255) NULL,
	[ValNominale] [varchar](255) NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO
select * from InfoProd
