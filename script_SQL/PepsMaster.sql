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
	[Actif] [varchar](255) NULL,
	[Date] [varchar](255) NULL,
	[High] [varchar](255) NULL,
	[Low] [varchar](255) NULL,
	[Open] [varchar](255) NULL,
	[Close] [varchar](255) NULL
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

BULK 
INSERT dbo.PepsDB
FROM 'C:\Users\guillaume\Desktop\donnes_peps.csv'
WITH (
FIELDTERMINATOR = ';',
ROWTERMINATOR = '0x0A'
)
--Check the content of the table.
SELECT PepsDB.*
FROM PepsDB
GO