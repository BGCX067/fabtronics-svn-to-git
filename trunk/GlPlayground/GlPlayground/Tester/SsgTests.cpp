#include <gtest\gtest.h>
#include "Clock.h"
#include <chrono>
#include <thread>

#include "ssg.h"
#include <glload/gl_3_3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


TEST(Ssg, Initialize)
{
//	EXPECT_TRUE();
}

void dumpMat( const glm::mat4& mat )
{
	auto fMat = glm::value_ptr(mat);

	for ( int i=0; i< 16; i++ )
	{
		std::cout << " i " << std::setprecision (4) <<  fMat[i] << "\n";
	}
}

TEST(Ssg, FrameTimeMeasuring)
{
	SSG::SceneSpace root(nullptr);
	
	SSG::SceneSpace lh(root);
	SSG::SceneSpace ll(lh);

	SSG::SceneSpace rh(root);
	SSG::SceneSpace rl(rh);

	lh.Translate( glm::vec3(1.1f,2.2f,3.3f) );
	ll.Translate( glm::vec3(-2.2f,-3.5f,-4.7f) );
	
	rh.Translate( glm::vec3(10.0f,11.0f,12.0f) );
	//rh.RotateAxis(glm::vec3(0.0f, 1.0f, 0.0f ), 3.1415926f );

	auto res0 = lh.GetTransformationToRoot().GetMatrix();
	auto res1 = ll.GetTransformationToRoot().GetMatrix();
	auto res2 = rl.GetTransformationToRoot().GetMatrix();
	auto res3 = ll.GetTransformationToSpace(rl).GetMatrix();

	dumpMat(res0);
	dumpMat(res1);
	//dumpMat(res2);
	dumpMat(res3);
//
			std::cout << "\ndone";

//	RigidTransformation rt;


	//SsgTransformation ssgt;
	//ssgt.Scale(glm::vec3( 2.1f, 2.2f, 2.3f));
	//ssgt.Translate(glm::vec3( 1.1f, 2.2f, 3.3f));


	//EXPECT_TRUE(clock.Initialize());

	//const int NUMTESTS = 2 + rand() % 5;
	//const float THRESHOLD = 0.03f;


	//for (int i=0; i< NUMTESTS; i++)
	//{
	//	std::cout << ".";

	//	clock.NewFrame();
	//	int thisTestMilliseconds = rand() % 10000;
	//	float thisTestSeconds = thisTestMilliseconds / 1000.0f;

	//	sleep(thisTestMilliseconds);
	//	clock.NewFrame();
	//	float elapsedSeconds = clock.TimeElapsedLastFrame();

	//	EXPECT_TRUE( ( thisTestSeconds -THRESHOLD ) < elapsedSeconds  );
	//	EXPECT_TRUE( elapsedSeconds < ( thisTestSeconds + THRESHOLD ) );
	//}

	//clock.NewFrame();
	//clock.TimeElapsedLastFrame();

	//EXPECT_TRUE(clock.Shutdown());
}

