#include "gtest/gtest.h"
#include "point2d.h"

class Point2DTest : public testing::Test {
    protected:
        virtual void SetUp() {
            point_ = new Point2D(0.0, 0.0);
        }
        virtual void TearDown() {
            delete point_;
        }
        Point2D *point_;
};

TEST_F(Point2DTest, basic) {
    /* Empty test */
}

TEST_F(Point2DTest, methods) {
    EXPECT_EQ(0.0, point_->getX());
    EXPECT_EQ(0.0, point_->getY());
}
