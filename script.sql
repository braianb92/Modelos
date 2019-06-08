USE [Biblioteca]
GO
/****** Object:  Table [dbo].[Autor]    Script Date: 8/6/2019 19:31:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Autor](
	[Id_Autor] [int] IDENTITY(1,1) NOT NULL,
	[nombreAutor] [varchar](50) NULL,
	[apellidoAutor] [varchar](50) NULL,
 CONSTRAINT [PK_Autor] PRIMARY KEY CLUSTERED 
(
	[Id_Autor] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Editorial]    Script Date: 8/6/2019 19:31:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Editorial](
	[Id_Editorial] [int] IDENTITY(1,1) NOT NULL,
	[nombreEditorial] [varchar](50) NULL,
 CONSTRAINT [PK_Editorial] PRIMARY KEY CLUSTERED 
(
	[Id_Editorial] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Genero]    Script Date: 8/6/2019 19:31:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Genero](
	[Id_Genero] [int] IDENTITY(1,1) NOT NULL,
	[nombreGenero] [varchar](50) NULL,
 CONSTRAINT [PK_Genero] PRIMARY KEY CLUSTERED 
(
	[Id_Genero] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Lib_Aut]    Script Date: 8/6/2019 19:31:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Lib_Aut](
	[Id_Libro] [int] NOT NULL,
	[Id_Autor] [int] NOT NULL,
 CONSTRAINT [PK_Lib_Aut] PRIMARY KEY CLUSTERED 
(
	[Id_Libro] ASC,
	[Id_Autor] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Libros]    Script Date: 8/6/2019 19:31:52 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Libros](
	[Id_Libro] [int] IDENTITY(1,1) NOT NULL,
	[titulo] [varchar](50) NULL,
	[Id_Genero] [int] NULL,
	[Id_Editorial] [int] NULL,
 CONSTRAINT [PK_Libros] PRIMARY KEY CLUSTERED 
(
	[Id_Libro] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[Autor] ON 

INSERT [dbo].[Autor] ([Id_Autor], [nombreAutor], [apellidoAutor]) VALUES (1, N'Oscar', N'Wilde')
INSERT [dbo].[Autor] ([Id_Autor], [nombreAutor], [apellidoAutor]) VALUES (2, N'Joanne', N'Rowling')
INSERT [dbo].[Autor] ([Id_Autor], [nombreAutor], [apellidoAutor]) VALUES (3, N'Eduardo', N'Kastika')
SET IDENTITY_INSERT [dbo].[Autor] OFF
SET IDENTITY_INSERT [dbo].[Editorial] ON 

INSERT [dbo].[Editorial] ([Id_Editorial], [nombreEditorial]) VALUES (1, N'Santillana Global')
INSERT [dbo].[Editorial] ([Id_Editorial], [nombreEditorial]) VALUES (2, N'Bloomsbury Publishing')
INSERT [dbo].[Editorial] ([Id_Editorial], [nombreEditorial]) VALUES (3, N'The Court and Society Review')
INSERT [dbo].[Editorial] ([Id_Editorial], [nombreEditorial]) VALUES (4, N'Innovar')
SET IDENTITY_INSERT [dbo].[Editorial] OFF
SET IDENTITY_INSERT [dbo].[Genero] ON 

INSERT [dbo].[Genero] ([Id_Genero], [nombreGenero]) VALUES (1, N'Ficción')
INSERT [dbo].[Genero] ([Id_Genero], [nombreGenero]) VALUES (2, N'Terror')
INSERT [dbo].[Genero] ([Id_Genero], [nombreGenero]) VALUES (3, N'Novela')
INSERT [dbo].[Genero] ([Id_Genero], [nombreGenero]) VALUES (4, N'LITERATURA ECONOMIA Y EMPRESA')
SET IDENTITY_INSERT [dbo].[Genero] OFF
INSERT [dbo].[Lib_Aut] ([Id_Libro], [Id_Autor]) VALUES (1, 1)
INSERT [dbo].[Lib_Aut] ([Id_Libro], [Id_Autor]) VALUES (2, 1)
INSERT [dbo].[Lib_Aut] ([Id_Libro], [Id_Autor]) VALUES (3, 2)
INSERT [dbo].[Lib_Aut] ([Id_Libro], [Id_Autor]) VALUES (4, 3)
SET IDENTITY_INSERT [dbo].[Libros] ON 

INSERT [dbo].[Libros] ([Id_Libro], [titulo], [Id_Genero], [Id_Editorial]) VALUES (1, N'The Picture of Dorian Gray', 1, 1)
INSERT [dbo].[Libros] ([Id_Libro], [titulo], [Id_Genero], [Id_Editorial]) VALUES (2, N'The Canterville Ghost ', 2, 3)
INSERT [dbo].[Libros] ([Id_Libro], [titulo], [Id_Genero], [Id_Editorial]) VALUES (3, N'Harry Potter', 3, 2)
INSERT [dbo].[Libros] ([Id_Libro], [titulo], [Id_Genero], [Id_Editorial]) VALUES (4, N'Introduccion a la Creatividad', 4, 4)
SET IDENTITY_INSERT [dbo].[Libros] OFF
ALTER TABLE [dbo].[Lib_Aut]  WITH CHECK ADD  CONSTRAINT [FK_Lib_Aut_Autor] FOREIGN KEY([Id_Autor])
REFERENCES [dbo].[Autor] ([Id_Autor])
GO
ALTER TABLE [dbo].[Lib_Aut] CHECK CONSTRAINT [FK_Lib_Aut_Autor]
GO
ALTER TABLE [dbo].[Lib_Aut]  WITH CHECK ADD  CONSTRAINT [FK_Lib_Aut_Libros] FOREIGN KEY([Id_Libro])
REFERENCES [dbo].[Libros] ([Id_Libro])
GO
ALTER TABLE [dbo].[Lib_Aut] CHECK CONSTRAINT [FK_Lib_Aut_Libros]
GO
ALTER TABLE [dbo].[Libros]  WITH CHECK ADD  CONSTRAINT [FK_Libros_Editorial] FOREIGN KEY([Id_Editorial])
REFERENCES [dbo].[Editorial] ([Id_Editorial])
GO
ALTER TABLE [dbo].[Libros] CHECK CONSTRAINT [FK_Libros_Editorial]
GO
ALTER TABLE [dbo].[Libros]  WITH CHECK ADD  CONSTRAINT [FK_Libros_Genero] FOREIGN KEY([Id_Genero])
REFERENCES [dbo].[Genero] ([Id_Genero])
GO
ALTER TABLE [dbo].[Libros] CHECK CONSTRAINT [FK_Libros_Genero]
GO
