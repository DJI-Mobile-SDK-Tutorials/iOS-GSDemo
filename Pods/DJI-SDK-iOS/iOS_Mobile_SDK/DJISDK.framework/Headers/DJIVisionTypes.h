//
//  DJIVisionTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJISDKFoundation.h"


/**
 *  Position of the sensor on the aircraft.
 */
typedef NS_ENUM(NSUInteger, DJIVisionSensorPosition) {
 

    /**
     *  The sensor is on the front or nose of the aircraft.
     */
    DJIVisionSensorPositionNose,
 

    /**
     *  The sensor is on the back or tail of the aircraft.
     */
    DJIVisionSensorPositionTail,
 

    /**
     *  The sensor is on the right or starboard side of the aircraft.
     */
    DJIVisionSensorPositionRight,
 

    /**
     *  The sensor is on the left or port side of the aircraft.
     */
    DJIVisionSensorPositionLeft,
    

    /**
     *  Unknown.
     */
    DJIVisionSensorPositionUnknown,
};


/**
 *  Distance warning returned by each sector of the front vision system. Warning
 *  Level 4 is the most serious level.
 */
typedef NS_ENUM (NSInteger, DJIObstacleDetectionSectorWarning){
 

    /**
     *  The warning level is invalid. The sector cannot determine depth of the scene in
     *  front of it.
     */
    DJIObstacleDetectionSectorWarningInvalid,
 

    /**
     *  The distance between the obstacle detected by the sector and the aircraft is
     *  over 4 meters.
     */
    DJIObstacleDetectionSectorWarningLevel1,
 

    /**
     *  The distance between the obstacle detected by the sector and the aircraft is
     *  between 3 - 4 meters.
     */
    DJIObstacleDetectionSectorWarningLevel2,


    /**
     *  The distance between the obstacle detected by the sector and the aircraft is
     *  between 2 - 3 meters.
     */
    DJIObstacleDetectionSectorWarningLevel3,
 

    /**
     *  The distance between the obstacle detected by the sector and the aircraft is
     *  less than 2 meters.
     */
    DJIObstacleDetectionSectorWarningLevel4,
 

    /**
     *  The distance warning is unknown. This warning is returned when an exception
     *  occurs.
     */
    DJIObstacleDetectionSectorWarningUnknown = 0xFF
};


/**
 *  Distance warning returned by the front vision system. Warning Level 4 is the
 *  most serious level.
 */
typedef NS_ENUM (NSInteger, DJIVisionSystemWarning){
 

    /**
     *  The warning is invalid. The front vision system cannot determine depth of the
     *  scene in front of it.
     */
    DJIVisionSystemWarningInvalid,
 

    /**
     *  The distance between the obstacle detected by the vision system and the aircraft
     *  is safe (over 2 meters).
     */
    DJIVisionSystemWarningSafe,
 

    /**
     *  The distance between the obstacle detected by the vision system and the aircraft
     *  is dangerous (less than 2 meters).
     */
    DJIVisionSystemWarningDangerous,
 

    /**
     *  The distance warning is unknown. This warning is returned when an exception
     *  occurs.
     */
    DJIVisionSystemWarningUnknown = 0xFF
};


/**
 *  The vision system can see in front of the aircraft with a 60 degree horizontal
 *  field of view (FOV) and 55 degree  vertical FOV. The horizontal FOV is split
 *  into four equal sectors, and this class gives the distance and warning  level
 *  for one sector.
 */
@interface DJIObstacleDetectionSector : NSObject


/**
 *  The detected obstacle distance to the aircraft in meters.
 */
@property(nonatomic, readonly) double obstacleDistanceInMeters;


/**
 *  The warning level based on distance.
 */
@property(nonatomic, readonly) DJIObstacleDetectionSectorWarning warningLevel;

@end


/**
 *  This class gives state information about the product's vision sensors used for
 *  obstacle detection. The two  types of sensors used are dual camera sensors
 *  operating in the visible spectrum (dual-camera sensor) and  infrared time of
 *  flight (TOF) sensors. Note, Inspire 2's upwards-facing infrared TOF sensor is
 *  not returned  in this state. It is accessed through `DJIVisionControlState`.
 */
@interface DJIVisionDetectionState : NSObject


/**
 *  The vision sensor's position on the aircraft. For Phantom 4 Pro, there are 4
 *  vision sensors on the aircraft.  The sensors on the nose and tail are dual-
 *  camera sensors. The sensors on the left and right are infrared  time-of-flight
 *  (TOF) sensors.
 */
@property(nonatomic, readonly) DJIVisionSensorPosition position;


/**
 *  `YES` if the vision sensor is working.
 */
@property(nonatomic, readonly) BOOL isSensorBeingUsed;


/**
 *  Distance warning level between the obstacle and the aircraft. This is a
 *  combination of warning levels from each sector.
 */
@property(nonatomic, readonly) DJIVisionSystemWarning systemWarning;


/**
 *  The distance to the closest detected obstacle, in meters. It is only used when
 *  the sensor is an infrared TOF  sensor. The valid range is [0.3, 5.0]. Phantom 4
 *  Pro has two infrared sensors on its left and right. Both sensors have a
 *  70-degree horizontal field of view (FOV) and 20-degree vertical FOV. The value
 *  is always 0.0 if the sensor is a dual-camera sensor or the sensor is not working
 *  properly.
 */
@property(nonatomic, readonly) double obstacleDistanceInMeters;


/**
 *  The vision system can see in front of the aircraft with a 70 degree horizontal
 *  field of view (FOV) and 55-degree  vertical FOV for the Phantom 4. The
 *  horizontal FOV is split into four equal sectors and this array contains the
 *  distance and warning information for each sector. For Phantom 4, the horizontal
 *  FOV is separated into 4 sectors.
 */
@property(nullable, nonatomic, readonly) NSArray<DJIObstacleDetectionSector *> *detectionSectors;

@end


/**
 *  Landing protection status returned by the downward vision sensor.
 */
typedef NS_ENUM (NSInteger, DJIVisionLandingProtectionState){
 

    /**
     *  The aircraft is not executing auto-landing or the downward vision sensor has not
     *  started to analyze the ground yet.
     */
    DJIVisionLandingProtectionStateNone,
 

    /**
     *  The downward vision sensor is analyzing the ground at the landing zone.
     */
    DJIVisionLandingProtectionStateAnalyzing,
 

    /**
     *  The downward vision sensor's analysis failed. Either the auto-landing can be
     *  attempted again, or the user needs  to land the aircraft manually.
     */
    DJIVisionLandingProtectionStateAnalysisFailed,
 

    /**
     *  The ground is flat and the aircraft is safe to land automatically.
     */
    DJIVisionLandingProtectionStateSafeToLand,
 

    /**
     *  Landing area is not flat enough to be considered safe for landing. The aircraft
     *  should be moved to an area that  is more flat and an auto-land should be
     *  attempted again or the user should land the aircraft manually.
     */
    DJIVisionLandingProtectionStateNotSafeToLand,
 

    /**
     *  Unknown.
     */
    DJIVisionLandingProtectionStateUnknown = 0xFF
};


/**
 *  This class gives the aircraft's state, which is controlled by the intelligent
 *  flight assistant.
 */
@interface DJIVisionControlState : NSObject


/**
 *  `YES` if the aircraft is braking automatically to avoid collision.
 */
@property (nonatomic, readonly) BOOL isBraking;


/**
 *  YES if the aircraft will not ascend further because of an obstacle detected
 *  within 1m above it.
 */
@property (nonatomic, readonly) BOOL isAscentLimitedByObstacle;


/**
 *  `YES` if the aircraft is avoiding collision from an obstacle moving towards the
 *  aircraft.
 */
@property (nonatomic, readonly) BOOL isAvoidingActiveObstacleCollision;


/**
 *  YES if the aircraft is landing precisely.
 */
@property (nonatomic, readonly) BOOL isPerformingPrecisionLanding;


/**
 *  The aircraft's landing protection state. This status is valid when landing
 *  protection is enabled.
 */
@property (nonatomic, readonly) DJIVisionLandingProtectionState landingProtectionState;

@end
