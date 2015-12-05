-----------------------------
-- MANAGER
-----------------------------

INSERT INTO Manager
VALUES ('Yves Matton');
INSERT INTO Manager
VALUES ('Carlo Cassina');
INSERT INTO Manager
VALUES ('Michel Nandan');
INSERT INTO Manager
VALUES ('Quirin Muller');
INSERT INTO Manager
VALUES ('Malcolm Wilson');
INSERT INTO Manager
VALUES ('Marcin Czachorski');
INSERT INTO Manager
VALUES ('Jost Capito');
INSERT INTO Manager
VALUES ('Stephane Clismis');

-----------------------------
-- TYRE
-----------------------------

INSERT INTO Tyre
VALUES ('Michelin');
INSERT INTO Tyre
VALUES ('Good Year');
INSERT INTO Tyre
VALUES ('Continental');

-----------------------------
-- CAR
-----------------------------

INSERT INTO Car
VALUES ('Citroen DS3', 'Michelin');
INSERT INTO Car
VALUES ('Ford Fiesta RS', 'Good Year');
INSERT INTO Car
VALUES ('Volkswagen Polo R', 'Continental');
INSERT INTO Car
VALUES ('Hyundai i20', 'Michelin');

-----------------------------
-- OIC
-----------------------------
INSERT INTO OIC
VALUES ('Ooi Choon Ho', 'nop123', 0); -- abc123
INSERT INTO OIC
VALUES ('Lee Zhen Zhi', 'nfq987', 0); -- asd987
INSERT INTO OIC
VALUES ('Hoo Zheng Qi', 'bxq897', 0); -- okd897
INSERT INTO OIC
VALUES ('Tan Shou Heng', '123ufl', 0); -- 123hsy
INSERT INTO OIC
VALUES ('Lai Yik Sheng', '987olq', 0); -- 987byd
INSERT INTO OIC
VALUES ('Chong Ee Xen', 'nsq871', 0); -- afd871
INSERT INTO OIC
VALUES ('Stephen Chowy', 'ofl651', 0); -- bsy651

-----------------------------
-- TEAM
-----------------------------

INSERT INTO Team
VALUES ('Citroen Total Abu Dhabi WRT', 'France', 'http://www.wrc.com/en/wrc/teams/team/citroen-total-abu-dhabi-wrt/page/873-94-873--.html?h=2015/teams/2', 'helloworld', 'Group R', 'Yves Matton', 'Citroen DS3', 'Ooi Choon Ho');
INSERT INTO Team
VALUES ('F.W.R.T.', 'Italy', 'http://www.wrc.com/en/wrc/teams/team/f.w.r.t./page/873-94-873--.html?h=2015/teams/43', 'hello123', 'Group R', 'Carlo Cassina', 'Ford Fiesta RS', 'Lee Zhen Zhi');
INSERT INTO Team
VALUES ('Hyundai Mobis World Rally Team', 'Germany', 'http://www.wrc.com/en/wrc/teams/team/hyundai-mobis-world-rally-team/page/873-94-873--.html?h=2015/teams/59', 'help0982', 'Group N', 'Michel Nandan', 'Hyundai i20', 'Tan Shou Heng');
INSERT INTO Team
VALUES ('Hyundai Motorsport', 'Germany', 'http://www.wrc.com/en/wrc/teams/team/hyundai-motorsport/page/873-94-873--.html?h=2015/teams/10', 'pop1283', 'Group RGT', 'Michel Nandan', 'Hyundai i20', 'Ooi Choon Ho');
INSERT INTO Team
VALUES ('Jipocar Czech Nation Team', 'Czech Republic', 'http://www.wrc.com/en/wrc/teams/team/jipocar-czech-national-team/page/873-94-873--.html?h=2015/teams/5', 'oiw1231', 'Group N', 'Quirin Muller', 'Ford Fiesta RS', 'Hoo Zheng Qi');
INSERT INTO Team
VALUES ('M-Sport World Rally Team', 'United Kingdom', 'http://www.wrc.com/en/wrc/teams/team/m-sport-world-rally-team/page/873-94-873--.html?h=2015/teams/4', 'kiu9283', 'Group R', 'Malcolm Wilson', 'Ford Fiesta RS', 'Lee Zhen Zhi');
INSERT INTO Team
VALUES ('RK World Rally Team', 'Poland', 'http://www.wrc.com/en/wrc/teams/team/rk-world-rally-team/page/873-94-873--.html?h=2015/teams/99', 'jus81726', 'Super 2000', 'Marcin Czachorski', 'Ford Fiesta RS', 'Hoo Zheng Qi');
INSERT INTO Team
VALUES ('Volkswagen Motorsport', 'Germany', 'http://www.wrc.com/en/wrc/teams/team/volkswagen-motorsport/page/873-94-873--.html?h=2015/teams/1', 'ous1123', 'Super 2000', 'Jost Capito', 'Volkswagen Polo R', 'Lai Yik Sheng');
INSERT INTO Team
VALUES ('Volkswagen Motorsport II', 'Germany', 'http://www.wrc.com/en/wrc/teams/team/volkswagen-motorsport-ii/page/873-94-873--.html?h=2015/teams/9', 'vus17263', 'Group N', 'Jost Capito', 'Volkswagen Polo R', 'Tan Shou Heng');
INSERT INTO Team
VALUES ('PH Sport', 'France', 'https://en.wikipedia.org/wiki/Citro%C3%ABn_World_Rally_Team', 'pieu123', 'Group R', 'Stephane Clismis', 'Citroen DS3', 'Lai Yik Sheng');

-----------------------------
-- ITEM
-----------------------------
INSERT INTO Item
VALUES ('Wiper Blade', 5, 'Chong Ee Xen');
INSERT INTO Item
VALUES ('Battery', 9, 'Stephen Chowy');
INSERT INTO Item
VALUES ('Spark Plug', 10, 'Chong Ee Xen');
INSERT INTO Item
VALUES ('Brake Disc', 7, 'Stephen Chowy');
INSERT INTO Item
VALUES ('Timing Belt', 15, 'Chong Ee Xen');

-----------------------------
-- REQUEST
-----------------------------
INSERT INTO Request
VALUES (1, 3, '2015/12/03', '2015/12/08', 'Pending', 'F.W.R.T.', 'Brake Disc', 'Lee Zhen Zhi');
INSERT INTO Request
VALUES (2, 2, '2015/12/04', '2015/12/09', 'Pending', 'Volkswagen Motorsport', 'Spark Plug', 'Lai Yik Sheng');
INSERT INTO Request
VALUES (3, 2, '2015/12/05', '2015/12/10', 'Pending', 'PH Sport', 'Wiper Blade', 'Lai Yik Sheng');
INSERT INTO Request
VALUES (4, 1, '2015/12/05', '2015/12/10', 'Pending', 'Jipocar Czech Nation Team', 'Timing Belt', 'Hoo Zheng Qi');
INSERT INTO Request
VALUES (5, 1, '2015/12/05', '2015/12/10', 'Pending', 'Hyundai Mobis World Rally Team', 'Battery', 'Tan Shou Heng');
