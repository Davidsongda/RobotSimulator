/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/sensor_touch.h"
#include "../src/sensor_proximity.h"
#include "../src/sensor_distress.h"
#include "../src/sensor_entity_type.h"
#include "../src/entity_type.h"

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorTouch, Sanity) {
  csci3081::SensorTouch st;

  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorTouch>::value;
  EXPECT_TRUE(val);

  EXPECT_EQ(st.activated(), 0);
  EXPECT_EQ(st.point_of_contact().x, 0.0);
  EXPECT_EQ(st.point_of_contact().y, 0.0);
  EXPECT_EQ(st.angle_of_contact(), 0.0);
}

TEST(SensorTouch, Update) {                  // Getter and Setter Test
  csci3081::SensorTouch st;

  st.activated(1);
  st.point_of_contact(Position(1.0, 1.0));
  EXPECT_EQ(st.activated(), 1);
  EXPECT_EQ(st.point_of_contact().x, 1.0);
  EXPECT_EQ(st.point_of_contact().y, 1.0);
}

TEST(SensorTouch, Reset) {
  csci3081::SensorTouch st;

  st.activated(1);
  st.point_of_contact(Position(1.0, 1.0));
  EXPECT_EQ(st.activated(), 1);
  EXPECT_EQ(st.point_of_contact().x, 1.0);
  EXPECT_EQ(st.point_of_contact().y, 1.0);
  EXPECT_DOUBLE_EQ(st.angle_of_contact(), 45.0);

  st.Reset();
  EXPECT_EQ(st.angle_of_contact(), 0.0);
  EXPECT_EQ(st.point_of_contact().x, 0.0);
  EXPECT_EQ(st.point_of_contact().y, 0.0);
  EXPECT_EQ(st.activated(), 0);
}

TEST(SensorTouch, AcceptCollision) {
  csci3081::SensorTouch st;

  EventCollision ec;
  st.activated(1);
  st.point_of_contact(Position(1.0, 1.0));
  ec.collided(true);
  st.Accept(&ec);
  EXPECT_EQ(st.activated(), 1);
  EXPECT_EQ(st.point_of_contact().x,1.0);
  EXPECT_EQ(st.point_of_contact().y,1.0);
  ec.collided(false);
  st.Accept(&ec);
  EXPECT_EQ(st.activated(), 0);
}

TEST(SensorTouch, Destructor) {
  csci3081::SensorTouch st;
  st.~SensorTouch();
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorTouch>::value;
  EXPECT_FALSE(val);
}

// -----------------------------------------------------------------------


TEST(SensorProximity, Sanity) {
  csci3081::SensorProximity sp;

  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorProximity>::value;
  EXPECT_TRUE(val);

  EXPECT_EQ(sp.activated(), 0);
  EXPECT_EQ(sp.distance(), 0.0);
  EXPECT_EQ(sp.SensorPos().x, 0.0);
  EXPECT_EQ(sp.SensorPos().y, 0.0);
  EXPECT_EQ(sp.SensedPos().x, 0.0);
  EXPECT_EQ(sp.SensedPos().y, 0.0);

  EXPECT_EQ(sp.SensedRad(), 0.0);
  EXPECT_EQ(sp.SensorHd(), 0.0);
  EXPECT_EQ(sp.filed_of_view(), 0.0);

}

TEST(SensorProximity, update) {
  csci3081::SensorProximity sp;

  sp.activated(1);
  sp.SensorPos(Position(1.0, 1.0));
  sp.SensedPos(Position(2.0, 2.0));
  sp.SensedRad(1.0);
  sp.SensorHd(10.0);
  sp.distance(10.0);
  sp.filed_of_view(5.0);

  EXPECT_EQ(sp.activated(), 1);
  EXPECT_EQ(sp.distance(), 10.0);
  EXPECT_EQ(sp.SensorPos().x, 1.0);
  EXPECT_EQ(sp.SensorPos().y, 1.0);
  EXPECT_EQ(sp.SensedPos().x, 2.0);
  EXPECT_EQ(sp.SensedPos().y, 2.0);

  EXPECT_EQ(sp.SensedRad(), 1.0);
  EXPECT_EQ(sp.SensorHd(), 10.0);
  EXPECT_EQ(sp.filed_of_view(), 5.0);
}

TEST(SensorProximity, Reset) {
  csci3081::SensorProximity sp;

  sp.activated(1);
  sp.SensorPos(Position(1.0, 1.0));
  sp.SensedPos(Position(2.0, 2.0));
  sp.SensedRad(1.0);
  sp.SensorHd(10.0);
  sp.distance(10.0);
  sp.filed_of_view(5.0);

  EXPECT_EQ(sp.activated(), 1);
  EXPECT_EQ(sp.distance(), 10.0);
  EXPECT_EQ(sp.SensorPos().x, 1.0);
  EXPECT_EQ(sp.SensorPos().y, 1.0);
  EXPECT_EQ(sp.SensedPos().x, 2.0);
  EXPECT_EQ(sp.SensedPos().y, 2.0);

  EXPECT_EQ(sp.SensedRad(), 1.0);
  EXPECT_EQ(sp.SensorHd(), 10.0);
  EXPECT_EQ(sp.filed_of_view(), 5.0);

  sp.Reset();
  EXPECT_EQ(sp.activated(), 0);
}

TEST(SensorProximity, InRange) {
  csci3081::SensorProximity sp;

  sp.activated(1);
  EXPECT_EQ(sp.InRange(Range(1.0,2.0), Range(2.0,1.0)), true);
  EXPECT_EQ(sp.InRange(Range(3.0,3.0), Range(2.0,4.0)), false);
}

TEST(SensorProximity, SensorReading) {
  csci3081::SensorProximity sp;

  sp.activated(1);
  sp.distance(3.0);
  EXPECT_EQ(sp.SensorReading(Position(1.0, 1.0), Position(2.0, 2.0), 1.0, 1.0), 23);
  sp.distance(1.0);
  sp.SensedRad(0.1);
  EXPECT_EQ(sp.SensorReading(Position(1.0, 1.0), Position(2.0, 1.0), 2.0, 1.0), -1);
}


TEST(SensorProximity, Destructor) {
  csci3081::SensorProximity sp;
  sp.~SensorProximity();
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorProximity>::value;
  EXPECT_FALSE(val);
}


// -----------------------------------------------------------------------

TEST(SensorDistress, Sanity) {
  csci3081::SensorDistress sd;

  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorDistress>::value;
  EXPECT_TRUE(val);

  EXPECT_EQ(sd.activated(), 0);
  EXPECT_EQ(sd.IsDistress(), 0);

  EXPECT_EQ(sd.SensorPos().x, 0.0);
  EXPECT_EQ(sd.SensorPos().y, 0.0);
  EXPECT_EQ(sd.SensedPos().x, 0.0);
  EXPECT_EQ(sd.SensedPos().y, 0.0);

  EXPECT_EQ(sd.SensedRad(), 0.0);
}

TEST(SensorDistress, update) {
  csci3081::SensorDistress sd;

  sd.activated(1);
  sd.range(10.0);
  sd.IsDistress(1);
  sd.SensorPos(Position(1.0, 1.0));
  sd.SensedPos(Position(2.0, 2.0));
  sd.SensedRad(1.0);

  EXPECT_EQ(sd.activated(), 1);
  EXPECT_EQ(sd.IsDistress(), 1);

  EXPECT_EQ(sd.SensorPos().x, 1.0);
  EXPECT_EQ(sd.SensorPos().y, 1.0);
  EXPECT_EQ(sd.SensedPos().x, 2.0);
  EXPECT_EQ(sd.SensedPos().y, 2.0);

  EXPECT_EQ(sd.SensedRad(), 1.0);
}

TEST(SensorDistress, Reset) {
  csci3081::SensorDistress sd;

  sd.activated(1);
  sd.range(10.0);
  sd.IsDistress(1);
  sd.SensorPos(Position(1.0, 1.0));
  sd.SensedPos(Position(2.0, 2.0));
  sd.SensedRad(1.0);
  EXPECT_EQ(sd.activated(), 1);
  EXPECT_EQ(sd.IsDistress(), 1);

  EXPECT_EQ(sd.SensorPos().x, 1.0);
  EXPECT_EQ(sd.SensorPos().y, 1.0);
  EXPECT_EQ(sd.SensedPos().x, 2.0);
  EXPECT_EQ(sd.SensedPos().y, 2.0);

  EXPECT_EQ(sd.SensedRad(), 1.0);

  sd.Reset();
  EXPECT_EQ(sd.activated(), 0);
}

TEST(SensorDistress, Destructor) {
  csci3081::SensorDistress sd;
  sd.~SensorDistress();
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorDistress>::value;
  EXPECT_FALSE(val);
}

TEST(SensorDistress, AcceptDistress) {

  csci3081::SensorDistress sd;
  EventDistressCall ed;
  ed.SensorPos(Position(1.0, 1.0));
  ed.SensedPos(Position(2.0, 2.0));
  sd.activated(0);
  ed.Distressed(true);
  sd.Accept(&ed);
  EXPECT_EQ(sd.activated(), 1);
  EXPECT_EQ(sd.SensorPos().x, 1.0);
  EXPECT_EQ(sd.SensorPos().y, 1.0);
  EXPECT_EQ(sd.SensedPos().x, 2.0);
  EXPECT_EQ(sd.SensedPos().y, 2.0);
  ed.Distressed(false);
  sd.Accept(&ed);
  EXPECT_EQ(sd.activated(), 0);
}

// -----------------------------------------------------------------------

TEST(SensorEntityType, Sanity) {
  csci3081::SensorEntityType set;

  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorEntityType>::value;
  EXPECT_TRUE(val);

  EXPECT_EQ(set.activated(), 0);
  EXPECT_EQ(set.range(), 0.0);

  EXPECT_EQ(set.SensorPos().x, 0.0);
  EXPECT_EQ(set.SensorPos().y, 0.0);
  EXPECT_EQ(set.SensedPos().x, 0.0);
  EXPECT_EQ(set.SensedPos().y, 0.0);

  EXPECT_EQ(set.SensedRad(), 0.0);
  EXPECT_EQ(set.get_entity(), kRobot);
}

TEST(SensorEntityType, update) {
  csci3081::SensorEntityType set;

  set.activated(1);
  set.range(10.0);
  set.SensorPos(Position(1.0, 1.0));
  set.SensedPos(Position(2.0, 2.0));
  set.SensedRad(1.0);
  set.set_entity(kPlayer);

  EXPECT_EQ(set.activated(), 1);
  EXPECT_EQ(set.range(), 10.0);

  EXPECT_EQ(set.SensorPos().x, 1.0);
  EXPECT_EQ(set.SensorPos().y, 1.0);
  EXPECT_EQ(set.SensedPos().x, 2.0);
  EXPECT_EQ(set.SensedPos().y, 2.0);

  EXPECT_EQ(set.SensedRad(), 1.0);
  EXPECT_EQ(set.get_entity(), kPlayer);
}

TEST(SensorEntityType, Reset) {
  csci3081::SensorEntityType set;

  set.activated(1);
  set.range(10.0);
  set.SensorPos(Position(1.0, 1.0));
  set.SensedPos(Position(2.0, 2.0));
  set.SensedRad(1.0);
  set.set_entity(kPlayer);

  EXPECT_EQ(set.activated(), 1);
  EXPECT_EQ(set.range(), 10.0);

  EXPECT_EQ(set.SensorPos().x, 1.0);
  EXPECT_EQ(set.SensorPos().y, 1.0);
  EXPECT_EQ(set.SensedPos().x, 2.0);
  EXPECT_EQ(set.SensedPos().y, 2.0);

  EXPECT_EQ(set.SensedRad(), 1.0);
  EXPECT_EQ(set.get_entity(), kPlayer);

  set.Reset();
  EXPECT_EQ(set.activated(), 0);
}

TEST(SensorEntityType, Destructor) {
  csci3081::SensorEntityType set;
  set.~SensorEntityType();
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorEntityType>::value;
  EXPECT_FALSE(val);
}

TEST(SensorEntityType, AcceptTypeEmit) {
  csci3081::SensorEntityType set;
  EventTypeEmit ete;

  ete.SensorPos(Position(1.0, 1.0));
  ete.SensedPos(Position(2.0, 2.0));
  ete.set_entity(kPlayer);
  set.activated(0);
  ete.Typeemitted(true);
  set.Accept(&ete);
  EXPECT_EQ(set.activated(), 1);
  EXPECT_EQ(set.SensorPos().x, 1.0);
  EXPECT_EQ(set.SensorPos().y, 1.0);
  EXPECT_EQ(set.SensedPos().x, 2.0);
  EXPECT_EQ(set.SensedPos().y, 2.0);
  EXPECT_EQ(set.get_entity(), kPlayer);

  ete.Typeemitted(false);
  set.Accept(&ete);
  EXPECT_EQ(set.activated(), 0);
}
// -----------------------------------------------------------------------
