-- Theme - E-store

CREATE TABLE Categories
(
    CategoryID INT PRIMARY KEY IDENTITY(1,1),
    CategoryName NVARCHAR(100) NOT NULL,
    Description NVARCHAR(MAX)
);

CREATE TABLE Suppliers
(
    SupplierID INT PRIMARY KEY IDENTITY(1,1),
    SupplierName NVARCHAR(150) NOT NULL,
    ContactEmail NVARCHAR(100) UNIQUE,
    PhoneNumber NVARCHAR(20)
);

CREATE TABLE Products
(
    ProductID INT PRIMARY KEY IDENTITY(1,1),
    ProductName NVARCHAR(200) NOT NULL,
    Description NVARCHAR(MAX),
    Price DECIMAL(10, 2) NOT NULL CHECK (Price >= 0),
    StockQuantity INT NOT NULL CHECK (StockQuantity >= 0),
    CategoryID INT,
    SupplierID INT,
    DateAdded DATETIME2 DEFAULT GETDATE(),
    FOREIGN KEY (CategoryID) REFERENCES Categories(CategoryID),
    FOREIGN KEY (SupplierID) REFERENCES Suppliers(SupplierID)
);

CREATE TABLE Customers
(
    CustomerID INT PRIMARY KEY IDENTITY(1,1),
    FirstName NVARCHAR(50) NOT NULL,
    LastName NVARCHAR(50) NOT NULL,
    Email NVARCHAR(100) NOT NULL UNIQUE,
    PasswordHash NVARCHAR(256) NOT NULL,
    RegistrationDate DATETIME2 DEFAULT GETDATE()
);


CREATE TABLE Addresses
(
    AddressID INT PRIMARY KEY IDENTITY(1,1),
    CustomerID INT NOT NULL,
    AddressLine1 NVARCHAR(255) NOT NULL,
    AddressLine2 NVARCHAR(255),
    City NVARCHAR(100) NOT NULL,
    PostalCode NVARCHAR(20) NOT NULL,
    Country NVARCHAR(100) NOT NULL,
    IsDefault BIT DEFAULT 0,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);

CREATE TABLE Shippers
(
    ShipperID INT PRIMARY KEY IDENTITY(1,1),
    ShipperName NVARCHAR(100) NOT NULL,
    TrackingURL NVARCHAR(255)
);

CREATE TABLE Promotions
(
    PromotionID INT PRIMARY KEY IDENTITY(1,1),
    PromoCode NVARCHAR(20) UNIQUE NOT NULL,
    DiscountPercentage DECIMAL(5, 2) NOT NULL CHECK (DiscountPercentage > 0 AND DiscountPercentage <= 100),
    ExpiryDate DATE NOT NULL,
    IsActive BIT DEFAULT 1
);

CREATE TABLE Orders
(
    OrderID INT PRIMARY KEY IDENTITY(1,1),
    CustomerID INT NOT NULL,
    OrderDate DATETIME2 DEFAULT GETDATE(),
    ShippingAddressID INT NOT NULL,
    ShipperID INT,
    OrderStatus NVARCHAR(50) DEFAULT 'Pending',
    TotalAmount DECIMAL(12, 2) NOT NULL,
    PromotionID INT,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    FOREIGN KEY (ShippingAddressID) REFERENCES Addresses(AddressID),
    FOREIGN KEY (ShipperID) REFERENCES Shippers(ShipperID),
    FOREIGN KEY (PromotionID) REFERENCES Promotions(PromotionID)
);


CREATE TABLE OrderDetails
(
    OrderDetailID INT PRIMARY KEY IDENTITY(1,1),
    OrderID INT NOT NULL,
    ProductID INT NOT NULL,
    Quantity INT NOT NULL CHECK (Quantity > 0),
    UnitPrice DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID),
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID)
);

CREATE TABLE Payments
(
    PaymentID INT PRIMARY KEY IDENTITY(1,1),
    OrderID INT NOT NULL,
    PaymentDate DATETIME2 DEFAULT GETDATE(),
    PaymentMethod NVARCHAR(50) NOT NULL,
    TransactionID NVARCHAR(255) UNIQUE,
    Amount DECIMAL(12, 2) NOT NULL,
    PaymentStatus NVARCHAR(50) DEFAULT 'Completed',
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID)
);

CREATE TABLE Reviews
(
    ReviewID INT PRIMARY KEY IDENTITY(1,1),
    ProductID INT NOT NULL,
    CustomerID INT NOT NULL,
    Rating INT NOT NULL CHECK (Rating >= 1 AND Rating <= 5),
    Comment NVARCHAR(MAX),
    ReviewDate DATETIME2 DEFAULT GETDATE(),
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID),
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);
