#include "../../../catch/catch.hpp"
#include "../bodies/Sphere.h"
#include "../bodies/Parallelepiped.h"
#include "../bodies/Cylinder.h"
#include "../bodies/Cone.h"
#include "../bodies/Compound.h"

/*СФЕРА*/
const double DENSITY_SPHERE = 30;
const double RADIUS_SPHERE = 3;
const double MASS_SPHERE = 3392.92;
const double VOLUME_SPHERE = 113.097;
const std::string STRING_SPHERE = "Body type is sphere. Massa is 3392.92. Volume is 113.097. Density is 30. Radius is 3.";

TEST_CASE("Check sphera")
{
	CSphere sphere(DENSITY_SPHERE, RADIUS_SPHERE);

	/*Проверяем, есть ли у тела плотность*/
	REQUIRE(sphere.GetDensity() == DENSITY_SPHERE);

	/*Проверяем, есть ли у сферы радиус*/
	REQUIRE(sphere.GetRadius() == RADIUS_SPHERE);

	/*Проверяем, нахождение объема у сферы*/
	REQUIRE(round(sphere.GetVolume() * 1000) / 1000 == VOLUME_SPHERE);

	/*Проверяем, нахождение массы у сферы*/
	REQUIRE(round(sphere.GetMass() * 1000) / 1000 == MASS_SPHERE);

	REQUIRE(sphere.ToString() == STRING_SPHERE);
};

/*ПАРАЛЛЕЛЕПИПЕД*/

const double DENSITY_PARALLELEPIPED = 30;
const double HEIGHT_PARALLELEPIPED = 3;
const double WIDTH_PARALLELEPIPED = 4;
const double DEPTH_PARALLELEPIPED = 5;
const double MASS_PARALLELEPIPED = 1800;
const double VOLUME_PARALLELEPIPED = 60;
const std::string STRING_PARALLELEPIPED = "Body type is parallelepiped. Massa is 1800. Volume is 60. Density is 30. Height is 3. Width is 4. Depth is 5.";

TEST_CASE("Check parallelepiped")
{
	CParallelepiped parallelepiped(DENSITY_PARALLELEPIPED, HEIGHT_PARALLELEPIPED, WIDTH_PARALLELEPIPED, DEPTH_PARALLELEPIPED);

	/*Проверяем, есть ли у тела плотность*/
	REQUIRE(parallelepiped.GetDensity() == DENSITY_PARALLELEPIPED);

	/*Проверяем, есть ли у параллелепипеда высота*/
	REQUIRE(parallelepiped.GetHeight() == HEIGHT_PARALLELEPIPED);

	/*Проверяем, есть ли у параллелепипеда ширина*/
	REQUIRE(parallelepiped.GetWidth() == WIDTH_PARALLELEPIPED);

	/*Проверяем, есть ли у параллелепипеда глубина*/
	REQUIRE(parallelepiped.GetDepth() == DEPTH_PARALLELEPIPED);

	/*Проверяем, нахождение объема у сферы*/
	REQUIRE(round(parallelepiped.GetVolume() * 1000) / 1000 == VOLUME_PARALLELEPIPED);

	/*Проверяем, нахождение массы у сферы*/
	REQUIRE(round(parallelepiped.GetMass() * 1000) / 1000 == MASS_PARALLELEPIPED);

	REQUIRE(parallelepiped.ToString() == STRING_PARALLELEPIPED);
};

/*ЦИЛИНДР*/

const double DENSITY_CYLINDER = 30;
const double RADIUS_CYLINDER = 3;
const double HEIGHT_CYLINDER = 10;
const double MASS_CYLINDER = 8482.3;
const double VOLUME_CYLINDER = 282.743;
const std::string STRING_CYLINDER  = "Body type is cylinder. Massa is 8482.3. Volume is 282.743. Density is 30. Base radius is 3. Height is 10.";

TEST_CASE("Check cylinder")
{
	CCylinder cylinder(DENSITY_CYLINDER, RADIUS_CYLINDER, HEIGHT_CYLINDER);

	REQUIRE(cylinder.GetDensity() == DENSITY_CYLINDER);

	/*Проверяем, есть ли у цилиндра радиус*/
	REQUIRE(cylinder.GetBaseRadius() == RADIUS_CYLINDER);

	/*Проверяем, есть ли у цилиндра высота*/
	REQUIRE(cylinder.GetHeight() == HEIGHT_CYLINDER);

	/*Проверяем, нахождение объема у цилиндра*/
	REQUIRE(round(cylinder.GetVolume() * 1000) / 1000 == VOLUME_CYLINDER);

	/*Проверяем, нахождение массы у цилиндра*/
	REQUIRE(round(cylinder.GetMass() * 1000) / 1000 == MASS_CYLINDER);

	REQUIRE(cylinder.ToString() == STRING_CYLINDER);
};

/*КОНУС*/

const double DENSITY_CONE = 30;
const double RADIUS_CONE = 3;
const double HEIGHT_CONE = 10;
const double MASS_CONE = 2827.433;
const double VOLUME_CONE = 94.248;
const std::string STRING_CONE = "Body type is cone. Massa is 2827.43. Volume is 94.248. Density is 30. Base radius is 3. Height is 10.";

TEST_CASE("Check cone")
{
	CCone cone(DENSITY_CONE, RADIUS_CONE, HEIGHT_CONE);

	/*Проверяем, есть ли у конуса плотность*/
	REQUIRE(cone.GetDensity() == DENSITY_CONE);

	/*Проверяем, есть ли у конуса радиус*/
	REQUIRE(cone.GetBaseRadius() == RADIUS_CONE);

	/*Проверяем, есть ли у конуса высота*/
	REQUIRE(cone.GetHeight() == HEIGHT_CONE);

	/*Проверяем, нахождение объема у конуса*/
	REQUIRE(round(cone.GetVolume() * 1000) / 1000 == VOLUME_CONE);

	/*Проверяем, нахождение массы у конуса*/
	REQUIRE(round(cone.GetMass() * 1000) / 1000 == MASS_CONE);

	REQUIRE(cone.ToString() == STRING_CONE);
};

/*СОСТОВНОЕ ТЕЛО*/

const double MASS_COMPOUND = 5192.92;
const double VOLUME_COMPOUND = 173.097;
const double DENSITY_COMPOUND = 30;
const std::string STRING_COMPOUND = "Body type is compound. Massa is 5192.92. Volume is 173.097. Density is 30. ""\n{""\nBody type is parallelepiped. Massa is 1800. Volume is 60. Density is 30. Height is 3. Width is 4. Depth is 5.""\nBody type is sphere. Massa is 3392.92. Volume is 113.097. Density is 30. Radius is 3.""\n}";

TEST_CASE("Check compound body")
{
	CCompound comp;

	/*Проверяем, нахлждение массы, объема и плотности у пустого составного тела*/
	REQUIRE(comp.GetDensity() == 0);
	REQUIRE(comp.GetMass() == 0);
	REQUIRE(comp.GetVolume() == 0);

	/*Проверяем, нахлждение массы, объема и плотности у составного тела*/
	REQUIRE(comp.AddChildBody(std::make_shared<CParallelepiped>(DENSITY_PARALLELEPIPED, HEIGHT_PARALLELEPIPED, WIDTH_PARALLELEPIPED, DEPTH_PARALLELEPIPED)));
	REQUIRE(comp.AddChildBody(std::make_shared<CSphere>(DENSITY_SPHERE, RADIUS_SPHERE)));

	REQUIRE(comp.ToString() == STRING_COMPOUND);

	REQUIRE(round(comp.GetMass() * 1000) / 1000 == MASS_COMPOUND);
	REQUIRE(round(comp.GetVolume() * 1000) / 1000 == VOLUME_COMPOUND);
	REQUIRE(round(comp.GetDensity() * 1000) / 1000 == DENSITY_COMPOUND);
}

TEST_CASE("recursive")
{
	/*Проверка, запрета циклических ссылок на объекты*/
	std::shared_ptr<CCompound> a = std::make_shared<CCompound>();
	std::shared_ptr<CCompound> b = std::make_shared<CCompound>();
	std::shared_ptr<CCompound> c = std::make_shared<CCompound>();
	std::shared_ptr<CCone> cone = std::make_shared<CCone>(DENSITY_CONE, RADIUS_CONE, HEIGHT_CONE);
 	REQUIRE(a->AddChildBody(b));
	REQUIRE(b->AddChildBody(c));
	REQUIRE(!c->AddChildBody(a));
	REQUIRE(a->AddChildBody(cone));
	REQUIRE(!c->AddChildBody(cone));
	REQUIRE(!c->AddChildBody(c));
	double mass = a->GetMass();
}