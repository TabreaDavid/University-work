USE hw1;
GO

INSERT INTO Categories (CategoryName, Description)
VALUES ('Gaming Stuff', 'games and gaming accessories'),
       ('Clothes', 'stuff to wear'),
       ('Books', 'textbooks and novels');

INSERT INTO Suppliers (SupplierName, ContactEmail, PhoneNumber)
VALUES ('eMAG', 'support@emag.ro', '0721-234-567'),
       ('Zara Store', 'info@zara.com', '0745-678-901'),
       ('Carturesti', 'vanzari@carturesti.ro', '0733-456-789');

INSERT INTO Products (ProductName, Description, Price, StockQuantity, CategoryID, SupplierID)
VALUES ('PS5', 'playstation 5 console', 2499.99, 15, 1, 1),
       ('Hoodie', 'black hoodie size M', 149.99, 50, 2, 2),
       ('Database Systems Book', 'the book we use for class', 89.99, 30, 3, 3),
       ('Gaming Headset', 'RGB headset with mic', 249.99, 25, 1, 1);

INSERT INTO Customers (FirstName, LastName, Email, PasswordHash)
VALUES ('Alex', 'Popescu', 'alex.popescu@stud.acs.upb.ro', 'parola123'),
       ('Maria', 'Ionescu', 'maria.ionescu99@gmail.com', 'qwerty456'),
       ('Andrei', 'Constantinescu', 'andrei_const@yahoo.com', 'password789');


INSERT INTO Shippers (ShipperName, TrackingURL)
VALUES ('Fan Courier', 'https://fancourier.ro/awb-tracking'),
       ('Cargus', 'https://cargus.ro/tracking');

UPDATE Products
SET Price = Price * 0.9 WHERE CategoryID = 1 AND Price > 500;

UPDATE Customers
SET FirstName = 'Jonathan'
WHERE LastName LIKE 'D%' OR Email LIKE '%smith%';

UPDATE Products
SET StockQuantity = StockQuantity + 10
WHERE Price BETWEEN 10 AND 100 
  AND Description IS NOT NULL;

DELETE FROM Suppliers
WHERE ContactEmail IS NULL;

DELETE FROM Products
WHERE ProductID IN (SELECT ProductID FROM Products WHERE StockQuantity = 0);

-- a1.
SELECT ContactEmail as Email FROM Suppliers
UNION
SELECT Email FROM Customers;

-- a2.
SELECT FirstName as Name FROM Customers WHERE FirstName LIKE 'J%'
UNION ALL
SELECT SupplierName FROM Suppliers WHERE SupplierName LIKE 'T%' OR SupplierName LIKE 'F%';

-- b1.
SELECT CustomerID FROM Orders
INTERSECT
SELECT CustomerID FROM Reviews;

-- b2.
SELECT ProductID, ProductName FROM Products WHERE Price > 50
INTERSECT
SELECT ProductID, ProductName FROM Products WHERE ProductID IN (SELECT ProductID FROM Products WHERE StockQuantity > 30);

-- c1.
SELECT CustomerID, FirstName, LastName FROM Customers
EXCEPT
SELECT c.CustomerID, c.FirstName, c.LastName FROM Customers c
INNER JOIN Orders o ON c.CustomerID = o.CustomerID;

-- c2.
SELECT ProductID, ProductName FROM Products
WHERE ProductID NOT IN (SELECT ProductID FROM Reviews);

-- d1. INNER JOIN
SELECT o.OrderID, c.FirstName, c.LastName, o.OrderDate, o.TotalAmount
FROM Orders o
INNER JOIN Customers c ON o.CustomerID = c.CustomerID;

-- d2. LEFT JOIN
SELECT p.ProductName, p.Price, c.CategoryName
FROM Products p
LEFT JOIN Categories c ON p.CategoryID = c.CategoryID;

-- d3. RIGHT JOIN
SELECT s.SupplierName, p.ProductName, p.Price
FROM Products p
RIGHT JOIN Suppliers s ON p.SupplierID = s.SupplierID;

-- d4. FULL JOIN
SELECT o.OrderID, c.FirstName + ' ' + c.LastName as CustomerName, s.ShipperName
FROM Orders o
FULL JOIN Customers c ON o.CustomerID = c.CustomerID
FULL JOIN Shippers s ON o.ShipperID = s.ShipperID;

-- e1.
SELECT ProductName, Price
FROM Products
WHERE CategoryID IN (
    SELECT CategoryID 
    FROM Products 
    WHERE CategoryID IN (SELECT CategoryID FROM Categories)
    GROUP BY CategoryID 
    HAVING COUNT(*) > 1
);

-- e2.
SELECT FirstName, LastName, Email
FROM Customers
WHERE CustomerID IN (
    SELECT CustomerID FROM Orders WHERE OrderID IN (
        SELECT OrderID FROM OrderDetails WHERE UnitPrice > 50
    )
);

-- f1.
SELECT c.CustomerID, c.FirstName, c.LastName
FROM Customers c
WHERE EXISTS (SELECT 1 FROM Orders o WHERE o.CustomerID = c.CustomerID);

-- f2.
SELECT p.ProductID, p.ProductName, p.Price
FROM Products p
WHERE EXISTS (SELECT 1 FROM OrderDetails od WHERE od.ProductID = p.ProductID);

-- g1.
SELECT CategoryName, AvgPrice
FROM (
    SELECT c.CategoryName, AVG(p.Price) as AvgPrice
    FROM Products p
    INNER JOIN Categories c ON p.CategoryID = c.CategoryID
    GROUP BY c.CategoryName
) AS CategoryPrices;

-- g2.
SELECT CustomerName, OrderCount
FROM (
    SELECT c.FirstName + ' ' + c.LastName as CustomerName, COUNT(o.OrderID) as OrderCount
    FROM Customers c
    LEFT JOIN Orders o ON c.CustomerID = o.CustomerID
    GROUP BY c.CustomerID, c.FirstName, c.LastName
) AS CustomerOrders
WHERE OrderCount > 0;

-- h1.
SELECT c.CategoryName, COUNT(p.ProductID) as ProductCount
FROM Categories c
LEFT JOIN Products p ON c.CategoryID = p.CategoryID
GROUP BY c.CategoryName;

-- h2.
SELECT c.CategoryName, AVG(p.Price) as AvgPrice, COUNT(p.ProductID) as ProductCount
FROM Categories c
INNER JOIN Products p ON c.CategoryID = p.CategoryID
GROUP BY c.CategoryName
HAVING AVG(p.Price) > 20;

-- h3.
SELECT s.SupplierName, SUM(p.StockQuantity) as TotalStock
FROM Suppliers s
INNER JOIN Products p ON s.SupplierID = p.SupplierID
GROUP BY s.SupplierID, s.SupplierName
HAVING SUM(p.StockQuantity) > (SELECT AVG(StockQuantity) FROM Products);

-- h4.
SELECT YEAR(c.RegistrationDate) as RegYear, COUNT(c.CustomerID) as CustomerCount
FROM Customers c
GROUP BY YEAR(c.RegistrationDate)
HAVING COUNT(c.CustomerID) >= (SELECT MIN(cnt) FROM (SELECT COUNT(*) as cnt FROM Customers GROUP BY YEAR(RegistrationDate)) as SubQ);

-- i1.

-- h2. categories with average price over $20 using HAVING
SELECT c.CategoryName, AVG(p.Price) as AvgPrice, COUNT(p.ProductID) as ProductCount
FROM Categories c
INNER JOIN Products p ON c.CategoryID = p.CategoryID
GROUP BY c.CategoryName
HAVING AVG(p.Price) > 20;

-- h3
SELECT s.SupplierName, SUM(p.StockQuantity) as TotalStock
FROM Suppliers s
INNER JOIN Products p ON s.SupplierID = p.SupplierID
GROUP BY s.SupplierID, s.SupplierName
HAVING SUM(p.StockQuantity) > (SELECT AVG(StockQuantity) FROM Products);

-- h4
SELECT YEAR(c.RegistrationDate) as RegYear, COUNT(c.CustomerID) as CustomerCount
FROM Customers c
GROUP BY YEAR(c.RegistrationDate)
HAVING COUNT(c.CustomerID) >= (SELECT MIN(cnt) FROM (SELECT COUNT(*) as cnt FROM Customers GROUP BY YEAR(RegistrationDate)) as SubQ);


-- i1.
SELECT ProductName, Price
FROM Products
WHERE Price < ANY (SELECT AVG(Price) FROM Products WHERE CategoryID = 1 GROUP BY CategoryID);

-- i2.
SELECT ProductName, Price
FROM Products
WHERE Price > ALL (SELECT MAX(Price) FROM Products WHERE CategoryID = 3 GROUP BY CategoryID);

-- i3.
SELECT SupplierName
FROM Suppliers
WHERE SupplierID NOT IN (SELECT SupplierID FROM Products WHERE Price < 20);

-- i4.
SELECT ProductName, Price
FROM Products
WHERE ProductID NOT IN (SELECT ProductID FROM Products WHERE StockQuantity < 50);

SELECT ProductName, Price, Price * 0.85 as DiscountedPrice, StockQuantity * Price as TotalValue
FROM Products
WHERE CategoryID = 1;

SELECT o.OrderID, o.TotalAmount, o.TotalAmount * 1.1 as WithTax
FROM Orders o;

SELECT ProductName, StockQuantity, StockQuantity * Price as InventoryValue
FROM Products;

SELECT ProductName, Price, StockQuantity
FROM Products
WHERE (Price > 50 AND StockQuantity > 20) OR (CategoryID = 2 AND NOT Price < 15);

SELECT FirstName, LastName, Email
FROM Customers
WHERE (FirstName LIKE 'J%' OR LastName LIKE 'S%') AND NOT Email LIKE '%test%';

SELECT o.OrderID, o.TotalAmount
FROM Orders o
WHERE (TotalAmount > 100) AND NOT (ShipperID IS NULL);

SELECT DISTINCT CategoryID FROM Products;

SELECT DISTINCT SupplierID FROM Products;

SELECT DISTINCT YEAR(RegistrationDate) as RegYear FROM Customers;

SELECT ProductName, Price FROM Products ORDER BY Price DESC;

SELECT FirstName, LastName FROM Customers ORDER BY LastName, FirstName;

SELECT TOP 5 ProductName, Price FROM Products ORDER BY Price DESC;

SELECT TOP 3 CustomerID, TotalAmount FROM Orders ORDER BY TotalAmount DESC;

-- arithmetic expression example 1 - calculating discounted price
SELECT ProductName, Price, Price * 0.85 as DiscountedPrice, StockQuantity * Price as TotalValue
FROM Products
WHERE CategoryID = 1;

-- arithmetic expression example 2 - calculating total order value
SELECT o.OrderID, o.TotalAmount, o.TotalAmount * 1.1 as WithTax
FROM Orders o;

-- arithmetic expression example 3
SELECT ProductName, StockQuantity, StockQuantity * Price as InventoryValue
FROM Products;

-- complex WHERE with AND, OR, NOT, parentheses example 1
SELECT ProductName, Price, StockQuantity
FROM Products
WHERE (Price > 50 AND StockQuantity > 20) OR (CategoryID = 2 AND NOT Price < 15);

-- complex WHERE example 2
SELECT FirstName, LastName, Email
FROM Customers
WHERE (FirstName LIKE 'J%' OR LastName LIKE 'S%') AND NOT Email LIKE '%test%';

-- complex WHERE example 3
SELECT o.OrderID, o.TotalAmount
FROM Orders o
WHERE TotalAmount > 100 AND NOT (ShipperID IS NULL);

-- DISTINCT example 1
SELECT DISTINCT CategoryID FROM Products;

-- DISTINCT example 2
SELECT DISTINCT SupplierID FROM Products;

-- DISTINCT example 3
SELECT DISTINCT YEAR(RegistrationDate) as RegYear FROM Customers;

-- ORDER BY example 1
SELECT ProductName, Price FROM Products ORDER BY Price DESC;

SELECT FirstName, LastName FROM Customers ORDER BY LastName, FirstName;

SELECT TOP 5 ProductName, Price FROM Products ORDER BY Price DESC;

SELECT TOP 3 CustomerID, TotalAmount FROM Orders ORDER BY TotalAmount DESC;