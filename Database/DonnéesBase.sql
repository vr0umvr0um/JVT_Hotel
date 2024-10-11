
/* Fichier sql contenant les données "de base" de la base de données*/
/* Créateur : Jules Forest */
/* Implémentation : Vanessa Antivackis */

INSERT INTO Adresse(numero, rue, ville, codePostal, pays) VALUES 
	(7, 'Rue de la République', 'Lyon', 69001, 'France'),
	(203, 'Boulevard de la Liberté', 'Lille', 59000, 'France'),
	(39, 'Avenue de la Victoire', 'Marseille', 13200, 'France'),
	(31, 'Rue du Général Leclerc', 'Bordeaux', 33000, 'France'),
	(50, 'Boulevard de la Paix', 'Strasbourg', 67000, 'France'), /* 5 */ 
	(43, 'Rue de la Gare', 'Nantes', 44000, 'France'),
	(12, 'Avenue de la République', 'Toulouse', 31000, 'France'),
	(98, 'Boulevard de la Liberté', 'Nice', 6000, 'France'),
	(65, 'Rue du Général de Gaulle', 'Rennes', 35000, 'France'),
	(103, 'Avenue de la Victoire', 'Reims', 51100, 'France'), /* 10 */
	(5, 'Avenue de Compiegne', 'Lyon', 69002, 'France'),
	(32, 'Avenue de la Dame', 'Bordeaux', 33000, 'France'),
	(4, 'Rue des Pissenlits', 'Marseille', 13002, 'France'),
	(76, 'Rue des Rayons', 'Bordeaux', 33001, 'France'),
	(45, 'Route du Bois Foucher', 'Strasbourg', 67001, 'France'), /* 15 */
	(876, 'Avenue Stanislas', 'Paris', 75000, 'France'),
	(120, 'Boulevard Heurteloup', 'Paris', 75020, 'France'),
	(180, 'Boulevard de la Liberté', 'Nice', 6030, 'France'),
	(561, 'Rue du Cours Bleu', 'Paris', 75680, 'France'),
	(208, 'Avenue des Palissades', 'Reims', 51101, 'France') /* 20 */
; 



INSERT INTO Hotel(nomHotel, nbChambres, idAdresse) VALUES 
	('Hotel Oberkampf', 70, 1),
	('Hotel de la Villette', 110, 2),
	('Hotel de Belleville', 95, 3),
	('Hotel de Vaugirard', 130, 4),
	('Hotel de la République', 140, 5) /* 5 */
;


INSERT INTO `employe` (`numEmploye`, `poste`, `nomEmploye`, `prenomEmploye`, `mdpEmploye`, `estResponsable`, `mailEmploye`, `idHotel`) VALUES
(1, 'Réceptionniste', 'Dupont', 'Jean', 'ea474f7dcafda10146f1b82b1900cd4c544d3fb97a8c55e129a27faa1f2889f9', 0, 'jean.dupont@entreprise.com', 1), /* mdp1 */
(2, 'Manager', 'Durand', 'Marie', '044e84410d94b9bdd856cfe01da6a7834b95a860792c84513c64dcf12066cfb5', 0, 'marie.durand@entreprise.com', 1), /* mdp2 */
(3, 'Réceptionniste', 'Martin', 'Pierre', '054f16c7365e91509d242374660fe4fc12016ced1e82fe9078fb43cc8ba41020', 0, 'pierre.martin@entreprise.com', 1),/*mdp3*/
(4, 'Manager', 'Lefevre', 'Sophiee', '78965d853ab10797185a084a133da63bce7d5febe7d79710aef1597a0233312b', 1, 'sophie.lefevre@entreprise.com', 2),
(5, 'Réceptionniste', 'Lemoine', 'Luc', '66033b5759b9be7110dff139ea89b1235300e5363d5ac6adf6c696407c28747e', 0, 'luc.lemoine@entreprise.com', 2),
(6, 'Responsable d\'équipe', 'Moreau', 'Claire', '41eea29f92b4d39b39d9d5716911b8b1e575df3ea44ef800b0792e43a842c40c', 0, 'claire.moreau@entreprise.com', 2),
(7, 'Réceptionniste', 'Girard', 'Nicolas', '403508b11fc810087460491aa2321591eb044653c3533006cb6e7dd7053e82a9', 0, 'nicolas.girard@entreprise.com', 2),
(8, 'Responsable d\'équipe', 'Laroche', 'Julie', '2def3fb494a0ea4649713186dfc3fddc95d8c328ddbb0c55ded235b7dc9d0a8e', 1, 'julie.laroche@entreprise.com', 4),
(9, 'Réceptionniste', 'Leroy', 'Paul', '1624160888203e00404fc33d0d49a741a9db60a4ae48ed2e3d03d766cea49799', 0, 'paul.leroy@entreprise.com', 2),
(10, 'Réceptionniste', 'Roux', 'Céline', 'dcaa170a0609ec6e8e213102236ba93e2c71dc5aae42e2ca79688e062e99a2f4', 0, 'celine.roux@entreprise.com', 3),
(11, 'Réceptionniste', 'Marchand', 'Hugo', 'dba1a1b9b798784fa304484a5f7133d4155febbb78a7172732fb98584d139fec', 0, 'hugo.marchand@entreprise.com', 3),
(12, 'Réceptionniste', 'Simon', 'Zoé', '79a31ea16bf098dc7d6a88d48e58ad10e2bf98e0fb9826a166a89bdf96bb4f38', 0, 'zoe.simon@entreprise.com', 2),
(13, 'Patron', 'Thomas', 'Tom', 'cb5cdabf740138047374b7f79ea01bffe4b535cf0cb32a1ca0fc2e093b7dcaf6', 1, 'tom.thomas@entreprise.com', 1), /* mpd23 */
(14, 'Responsable d\'équipe', 'Robert', 'Nina', '453120caa4e8b13f2a4e5d6e88044d31ee44b61935f07b1bced718d103a80283', 0, 'nina.robert@entreprise.com', 4),
(15, 'Réceptionniste', 'Petit', 'Maxime', '536ef1927308a1038cddf05607c1a6898566b1e5d19929f76788d6e1b54af447', 0, 'maxime.petit@entreprise.com', 4),
(16, 'Réceptionniste', 'Lefebvre', 'Léonie', 'a10bde1079760ede67356e908633e35c5ce6e946a4e0ad4c67c5b26c9196848c', 0, 'leonie.lefebvre@entreprise.com', 4),
(17, 'Réceptionniste', 'Leroux', 'Mathis', '539fc5000e18204a314c12b9b2358760baea02b066cf89b379fcd04d00359662', 0, 'mathis.leroux@entreprise.com', 4),
(18, 'Patron', 'Morel', 'Maëlys', '0913642f9ccd9c6936fac0b2cd2cf4510fa1246ba15ce3d5f2e1497511efdd99', 1, 'maelys.morel@entreprise.com', 3),
(19, 'Manager', 'Fournier', 'Malo', 'cdc6242809c8f102dd7b20c3a54dbe601a09d4c3eb3511e8399ae732d28f59de', 1, 'malo.fournier@entreprise.com', 2),
(20, 'Patron', 'Vaurice', 'Chris', 'a8dbcd996a9463307e42fe51ab2329a91350b4779f8fbab663d6cf3d73850f69', 1, 'chris.vaurice@entreprise.com', 2),
(21, 'Patron', 'Dusoulier', 'Arnaud', '9c56cc51b374c3ba189210d5b6d4bf57790d351c96c47c02190ecf1e430635ab', 1, 'arnaud.dusoulier@entreprise.com', 4),
(22, 'Patron', 'Roche', 'Manon', '9e6dd12c9fd0a5f61da08aa8688a6ec11a0eda2c030fce6dece94f0e178cb8e4', 1, 'manon.roche@entreprise.com', 5),
(41, 'Réceptionniste', 'Dufour', 'Caroline', 'b71ec77da4320c84ef2b4d14be0f4472ae8378c6afeedac62601053cf69d9d10', 0, 'caroline.dufour@entreprise.com', 3),
(42, 'Manager', 'Laurent', 'Stella', '969c4054f2e6791a367c6e33eee733f390c483877df62f0643e2eb840c8fc4af', 1, 'stella.laurent@entreprise.com', 1);




INSERT INTO Chambre(prix, nbCouchages, idHotel) VALUES 
	(130, 2, 1),
	(130, 2, 1),
	(453, 3, 2),
	(450, 3, 2),
	(450, 3, 2), /* 5 */
	(200, 2, 2),
	(210, 2, 2),
	(230, 2, 2),
	(140, 2, 3),
	(120, 1, 3), /* 10 */
	(70, 1, 3),
	(890, 2, 4),
	(890, 2, 4),
	(890, 2, 4),
	(890, 2, 4), /* 15 */
	(1200, 2, 4),
	(967, 4, 4),
	(950, 4, 4),
	(1320, 5, 4),
	(93, 2, 5) /* 20 */
;


INSERT INTO `client` (`idClient`, `nomClient`, `prenomClient`, `telephone`, `mailClient`, `mdpClient`, `idAdresse`) VALUES
(1, 'Moreau', 'Claire', '0606020305', 'claire.moreau@mail.com', '41eea29f92b4d39b39d9d5716911b8b1e575df3ea44ef800b0792e43a842c40c', 6), /* mpd6 */
(2, 'Girard', 'Nicolas', '0607020304', 'nicolas.girard@mail.com', '403508b11fc810087460491aa2321591eb044653c3533006cb6e7dd7053e82a9', 7), /* mpd7 */
(3, 'Laroche', 'Julie', '0608020304', 'julie.laroche@mail.com', '2def3fb494a0ea4649713186dfc3fddc95d8c328ddbb0c55ded235b7dc9d0a8e', 6), /* mdp8 */
(4, 'Leroy', 'Paul', '0609020304', 'paul.leroy@mail.com', '1624160888203e00404fc33d0d49a741a9db60a4ae48ed2e3d03d766cea49799', 9), /* mpd9 */
(5, 'Roux', 'Céline', '0610020304', 'celine.roux@mail.com', 'dcaa170a0609ec6e8e213102236ba93e2c71dc5aae42e2ca79688e062e99a2f4', 10), /* mdp10 */
(6, 'Bertrand', 'François', '0611020304', 'francois.bertrand@mail.com', 'a17fe45f0c32343195fcf6c35b863060999542e420ff6012e551bfc137dd7f9c', 11),
(7, 'Blanchard', 'Emma', '0612020304', 'emma.blanchard@mail.com', '3f5175f1fb1309093ad56424e5f45211350a7084d0a81f3ad2eb4147cbb135c9', 12),
(8, 'Boyer', 'Louis', '0613020304', 'louis.boyer@mail.com', '6ca2031a836a291754c6219c7d235c6ecbed02aa2d47aaae2364f71e48f8c8e1', 13),
(9, 'Chevalier', 'Alice', '0614020304', 'alice.chevalier@mail.com', '6680da9a3f7651be820cd4be67cb15d752fb7372ebd4f45fc966b4c4bba48d67', 14),
(10, 'David', 'Gabriel', '0615020304', 'gabriel.david@mail.com', '248ad48bf2a8fa868be9c3de1e13198fe338171aa670091b93a031867f11f21f', 15),
(11, 'Denis', 'Chloé', '0616020304', 'chloe.denis@mail.com', '87916d429f09bbaca8e623a0180e2fa3c16567fb58dd37d2464b1fd0d0e3c58c', 16),
(12, 'Dumont', 'Nathan', '0617020304', 'nathan.dumont@mail.com', 'a9da6e237671f9f833f1dde8221103babcd180be199c77304387e14497909eb2', 11),
(13, 'Fournier', 'Inès', '0618020304', 'ines.fournier@mail.com', '38d054cab870b763c6dcd443c331684bdf90b4a7b2307b494386a8638b8479d2', 18),
(14, 'Gautier', 'Léo', '0619020304', 'leo.gautier@mail.com', '9f07863928eb6b5e829b0bfac3ea65890b14493672af16ee5801db6a9a69ca8a', 19),
(15, 'Guillaume', 'Léa', '0620020304', 'lea.guillaume@mail.com', '668745d372dfe0e31ea1267ee7641d872f3b997388875cd2aee5518bc0b17718', 20),
(23, 'Bridou', 'Justin', '0654789067', 'justin.bridou@mail.com', '373f0128ef62bba656668c91d76db86193f155e7a223e11f1ca2f91d111ca43c', 4),
(24, 'Nesquick', 'Coco', '0634567890', 'coco.nesquick@mail.com', '3bafba96c7c0b6c722cad69a8554b29c5b7c140813620dd2cdfe9acae91f93de', 5),
(25, 'Doe', 'Jane', '0612345678', 'jane.doe@mail.com', '7618385caea382f562305468e586330381aae549829075b78dca7cb0d0aefac6', 10);

INSERT INTO Reservation(dateArrive, dateDepart, estValide, estTraite, numChambre, idClient) VALUES 
	('2024-05-01', '2024-05-03', 0, 0, 1, 1),
	('2024-05-04', '2024-05-07', 0, 0, 2, 1),
	('2024-05-08', '2024-05-10', 0, 0, 3, 2),
	('2024-05-11', '2024-05-14', 0, 0, 4, 2),
	('2024-05-15', '2024-05-18', 0, 0, 5, 3), /* 5 */
	('2024-05-19', '2024-05-21', 0, 0, 6, 3),
	('2024-05-22', '2024-05-25', 0, 0, 7, 4),
	('2024-05-26', '2024-05-29', 0, 0, 8, 4),
	('2024-05-30', '2024-06-02', 0, 0, 9, 5),
	('2024-05-10', '2024-05-17', 0, 0, 6, 3), /* 10 */
	('2024-05-06', '2024-06-09', 0, 0, 7, 4),
	('2024-05-01', '2024-05-12', 0, 0, 8, 4),
	('2024-05-02', '2024-06-04', 0, 0, 9, 5),
	('2024-05-04', '2024-05-07', 0, 0, 6, 3),
	('2024-05-17', '2024-05-21', 0, 0, 7, 4), /* 15 */
	('2024-06-26', '2024-06-29', 0, 0, 8, 4),
	('2024-05-20', '2024-05-25', 0, 0, 9, 5),
	('2024-06-03', '2024-06-06', 0, 0, 10, 5),
	('2024-06-07', '2024-06-10', 0, 0, 1, 6),
	('2024-06-11', '2024-06-14', 0, 0, 2, 6), /* 20 */
	('2024-06-15', '2024-06-18', 0, 0, 3, 7),
	('2024-06-19', '2024-06-22', 0, 0, 4, 7),
	('2024-06-23', '2024-06-26', 0, 0, 5, 8),
	('2024-06-27', '2024-06-30', 0, 0, 6, 8),
	('2024-07-01', '2024-07-04', 0, 0, 7, 9), /* 25 */
	('2024-07-05', '2024-07-08', 0, 0, 8, 9),
	('2024-07-09', '2024-07-12', 0, 0, 9, 10),
	('2024-07-13', '2024-07-16', 0, 0, 10, 10),
	('2024-07-17', '2024-07-20', 0, 0, 1, 11),
	('2024-07-21', '2024-07-24', 0, 0, 2, 11), /* 30 */
	('2024-07-25', '2024-07-28', 0, 0, 3, 12),
	('2024-07-29', '2024-08-01', 0, 0, 4, 12),
	('2024-08-02', '2024-08-05', 0, 0, 5, 13), 
	('2024-08-06', '2024-08-09', 0, 0, 6, 13),
	('2024-08-10', '2024-08-13', 0, 0, 7, 14) /* 35 */
;

INSERT INTO administrateur (mailAdmin, mdpAdmin, pseudoAdmin) VALUES
	("forestjules5@gmail.com", "16687b6b4408496223ecc12f66673831ea93cddf0f19b8928a2f375d872c56bd", "Zorg"), /* mdp = "julesLPB" */
	("jhonKennedy@gmail.com", "54af2a2960e582263c45971cdd40da4ae31ede1db5395629d910f056479de12d", "XXXTentacion"), /* mdp = "jojo" */
	("momoCalinou@gmail.com", "fc008bdb48553a900bdbafcd64e5b1f567e79993418c1c1bdbae9cfa419caa19", "Le M"), /* mdp = "leplusbeau" */
	("annita.salawi@gmail.com", "03fc1174b7adb5fecf273c822adc0e31e62acc4ee8f992b09c2cb246bae1472f", "Anni"), /* mdp = "jaimeleschats" */
	("geralddarmanin@gmail.com", "8e3e78f88035edce3ddff47be7e4dea0ee9e8cb17d881311a986ce6da989e300", "CasseGenou") /* mdp = "vivelapolisse" */
;
