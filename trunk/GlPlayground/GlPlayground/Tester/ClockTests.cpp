//#include <gtest\gtest.h>
//#include "Clock.h"
//#include <chrono>
//#include <thread>
//
//TEST(Clock, Initialize)
//{
//	Clock clock;
//	EXPECT_TRUE(clock.Initialize());
//	EXPECT_TRUE(clock.Shutdown());
//}
//
//
//static void sleep( int msec )
//{
//	std::chrono::milliseconds dura( msec );
//    std::this_thread::sleep_for( dura );
//}
//
//TEST(Clock, FrameTimeMeasuring)
//{
//	Clock clock;
//	EXPECT_TRUE(clock.Initialize());
//
//	const int NUMTESTS = 2 + rand() % 5;
//	const float THRESHOLD = 0.03f;
//
//
//	for (int i=0; i< NUMTESTS; i++)
//	{
//		std::cout << ".";
//
//		clock.NewFrame();
//		int thisTestMilliseconds = rand() % 10000;
//		float thisTestSeconds = thisTestMilliseconds / 1000.0f;
//
//		sleep(thisTestMilliseconds);
//		clock.NewFrame();
//		float elapsedSeconds = clock.TimeElapsedLastFrame();
//
//		EXPECT_TRUE( ( thisTestSeconds -THRESHOLD ) < elapsedSeconds  );
//		EXPECT_TRUE( elapsedSeconds < ( thisTestSeconds + THRESHOLD ) );
//	}
//
//	clock.NewFrame();
//	clock.TimeElapsedLastFrame();
//
//	EXPECT_TRUE(clock.Shutdown());
//}
//
