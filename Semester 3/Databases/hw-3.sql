-- Lab 3: Database Versioning System
USE hw1;
GO

-- Version tracking table
CREATE TABLE DatabaseVersion (
    CurrentVersion INT
);
INSERT INTO DatabaseVersion VALUES (0);
GO

-- a. Modify column type
CREATE OR ALTER PROCEDURE v1_up AS
    ALTER TABLE Products ALTER COLUMN Description NVARCHAR(500);
GO

CREATE OR ALTER PROCEDURE v1_down AS
    ALTER TABLE Products ALTER COLUMN Description NVARCHAR(MAX);
GO

-- b. Add/Remove column
CREATE OR ALTER PROCEDURE v2_up AS
    ALTER TABLE Products ADD DiscountPrice DECIMAL(10,2);
GO

CREATE OR ALTER PROCEDURE v2_down AS
    ALTER TABLE Products DROP COLUMN DiscountPrice;
GO

-- c. Add/Remove DEFAULT constraint
CREATE OR ALTER PROCEDURE v3_up AS
    ALTER TABLE Products ADD CONSTRAINT DF_StockQuantity DEFAULT 0 FOR StockQuantity;
GO

CREATE OR ALTER PROCEDURE v3_down AS
    ALTER TABLE Products DROP CONSTRAINT DF_StockQuantity;
GO

-- d. Add/Remove primary key
CREATE OR ALTER PROCEDURE v4_up AS
    CREATE TABLE TestTable (TestID INT PRIMARY KEY, TestName NVARCHAR(50));
GO

CREATE OR ALTER PROCEDURE v4_down AS
    DROP TABLE TestTable;
GO

-- e. Add/Remove candidate key
CREATE OR ALTER PROCEDURE v5_up AS
    ALTER TABLE Products ADD CONSTRAINT UQ_ProductName UNIQUE (ProductName);
GO

CREATE OR ALTER PROCEDURE v5_down AS
    ALTER TABLE Products DROP CONSTRAINT UQ_ProductName;
GO

-- f. Add/Remove foreign key
CREATE OR ALTER PROCEDURE v6_up AS
BEGIN
    CREATE TABLE ProductReviews (ReviewID INT PRIMARY KEY IDENTITY, ProductID INT);
    ALTER TABLE ProductReviews ADD CONSTRAINT FK_Reviews FOREIGN KEY (ProductID) REFERENCES Products(ProductID);
END
GO

CREATE OR ALTER PROCEDURE v6_down AS
    DROP TABLE ProductReviews;
GO

-- g. Create/Drop table
CREATE OR ALTER PROCEDURE v7_up AS
    CREATE TABLE Wishlist (WishlistID INT PRIMARY KEY IDENTITY, CustomerID INT, ProductID INT);
GO

CREATE OR ALTER PROCEDURE v7_down AS
    DROP TABLE Wishlist;
GO

-- Main procedure: change to any version
CREATE OR ALTER PROCEDURE GoToVersion @target INT
AS
BEGIN
    DECLARE @current INT;
    SELECT @current = CurrentVersion FROM DatabaseVersion;
    
    -- Upgrade
    WHILE @current < @target
    BEGIN
        SET @current = @current + 1;
        IF @current = 1 EXEC v1_up;
        IF @current = 2 EXEC v2_up;
        IF @current = 3 EXEC v3_up;
        IF @current = 4 EXEC v4_up;
        IF @current = 5 EXEC v5_up;
        IF @current = 6 EXEC v6_up;
        IF @current = 7 EXEC v7_up;
    END
    
    -- Downgrade
    WHILE @current > @target
    BEGIN
        IF @current = 7 EXEC v7_down;
        IF @current = 6 EXEC v6_down;
        IF @current = 5 EXEC v5_down;
        IF @current = 4 EXEC v4_down;
        IF @current = 3 EXEC v3_down;
        IF @current = 2 EXEC v2_down;
        IF @current = 1 EXEC v1_down;
        SET @current = @current - 1;
    END
    
    UPDATE DatabaseVersion SET CurrentVersion = @target;
    PRINT 'Now at version ' + CAST(@target AS VARCHAR);
END
GO
