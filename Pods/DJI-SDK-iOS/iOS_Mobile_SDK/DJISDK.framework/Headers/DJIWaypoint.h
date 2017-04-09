//
//  DJIWaypoint.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "DJISDKFoundation.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  Maximum number of actions a single waypoint can have. The maximum supported
 *  number is 15.
 */
DJI_API_EXTERN const int DJIMaxActionCount;


/**
 *  Maximum number of times a single waypoint action can be repeated. The maximum
 *  supported number is 15.
 */
DJI_API_EXTERN const int DJIMaxActionRepeatTimes;


/**
 *  How the aircraft will turn at a waypoint to transition between headings.
 */
typedef NS_ENUM (NSUInteger, DJIWaypointTurnMode){


    /**
     *  Changes the heading of the aircraft by rotating the aircraft clockwise.
     */
    DJIWaypointTurnClockwise,


    /**
     *  Changes the heading of the aircraft by rotating the aircraft anti-clockwise.
     */
    DJIWaypointTurnCounterClockwise,
};


/**
 *  Waypoint action types.
 */
typedef NS_ENUM (NSUInteger, DJIWaypointActionType){


    /**
     *  Keeps the aircraft at the waypoint's location. The `actionParam`  parameter will
     *  determine how much time in milliseconds the aircraft will stay at the location
     *  with  range of [0, 32767] milliseconds.
     */
    DJIWaypointActionTypeStay,


    /**
     *  Starts to shoot a photo. The `actionParam` for the waypoint action will  be
     *  ignored. The maximum time set to execute this waypoint action is 6 seconds. If
     *  the time while executing  the waypoint action goes above 6 seconds, the aircraft
     *  will stop executing the waypoint action and will  move on to the next waypoint
     *  action, if one exists.
     */
    DJIWaypointActionTypeShootPhoto,


    /**
     *  Starts recording. The `actionParam` for the waypoint action will be  ignored.
     *  The maximum time set to execute this waypoint action is 6 seconds. If the time
     *  while executing  the waypoint action goes above 6 seconds (e.g. the camera is
     *  not present) the aircraft will stop executing  the waypoint action and will move
     *  on to the next waypoint action, if one exists.
     */
    DJIWaypointActionTypeStartRecord,


    /**
     *  Stops recording. The `actionParam` for the waypoint action will be ignored.  The
     *  maximum time set to execute this waypoint action is 6 seconds. If the time while
     *  executing the waypoint  action goes above 6 seconds (e.g. the camera is not
     *  present) the aircraft will stop executing the waypoint  action and will move on
     *  to the next waypoint action, if one exists.
     */
    DJIWaypointActionTypeStopRecord,


    /**
     *  Rotates the aircraft's yaw. The rotation direction is determined by the
     *  waypoint's `turnMode` property.  The `actionParam` value must be in the range of
     *  [-180, 180] degrees.
     */
    DJIWaypointActionTypeRotateAircraft,


    /**
     *  Rotates the gimbal's pitch. The actionParam value should be in range [-90, 0]
     *  degrees.
     */
    DJIWaypointActionTypeRotateGimbalPitch,
};


/**
 *  This class represents a waypoint action for `DJIWaypoint`. It determines what
 *  action is performed when  the aircraft reaches the corresponding waypoint.
 */
@interface DJIWaypointAction : NSObject


/**
 *  Waypoint action of type `DJIWaypointActionType` the aircraft will execute this
 *  action once  the aircraft reaches the waypoint. All possible actions are defined
 *  in the `DJIWaypointActionType` enum.
 */
@property(nonatomic, assign) DJIWaypointActionType actionType;


/**
 *  Action parameter for a waypoint action. See enum `DJIWaypointAction` for details
 *  on which  actions use `actionParam`.
 */
@property(nonatomic, assign) int16_t actionParam;


/**
 *  Initialize the class with a specific action type and corresponding parameter.
 *  
 *  @param type An enum value of `DJIWaypointActionType`.
 *  @param param corresponding parameter for action type.
 *  
 *  @return A `DJIWaypointAction` object initialized with `DJIWaypointActionType` Enum and an int16_t value of param.
 */
- (id)initWithActionType:(DJIWaypointActionType)type param:(int16_t)param;

@end


/**
 *  The class represents a target point in the waypoint mission. For a waypoint
 *  mission, a flight route  consists of multiple `DJIWaypoint` objects. The user
 *  can also define the actions to perform for  each `DJIWaypoint`.
 */
@interface DJIWaypoint : NSObject


/**
 *  Waypoint coordinate latitude and longitude in degrees.
 */
@property(nonatomic, assign) CLLocationCoordinate2D coordinate;


/**
 *  Altitude of the aircraft in meters when it reaches waypoint. The altitude of the
 *  aircraft is relative to  the ground at the take-off location, has a range of
 *  [-200,500], and should not be larger than the  aircraft's maximum altitude. If
 *  two adjacent waypoints have different altitudes, the altitude will  gradually
 *  change as the aircraft flys between waypoints.
 */
@property(nonatomic, assign) float altitude;


/**
 *  The heading to which the aircraft will rotate by the time it reaches the
 *  waypoint. The aircraft heading  will gradually change between two waypoints with
 *  different headings if the waypoint  mission's `headingMode` is set  to
 *  `DJIWaypointMissionHeadingUsingWaypointHeading`. A heading has a range of
 *  [-180, 180] degrees, where 0 represents True North.
 */
@property(nonatomic, assign) float heading;


/**
 *  Determines how many times the set of waypoint actions are repeated. The default
 *  value is one time, and  the maximum is `DJIMaxActionRepeatTimes`.
 */
@property(nonatomic, assign) NSUInteger actionRepeatTimes;


/**
 *  The maximum time set to execute all the waypoint actions for a waypoint. If the
 *  time while executing the  waypoint actions goes above the time set, the aircraft
 *  will stop executing the waypoint actions for the  current waypoint and will move
 *  on to the next waypoint. The value of this property must be in the range  of [0,
 *  999] seconds. The default value is 60 seconds.
 */
@property(nonatomic) int actionTimeoutInSeconds;


/**
 *  Corner radius of the waypoint. When the flight path mode  is
 *  `DJIWaypointMissionFlightPathCurved` the flight path near a waypoint will be  a
 *  curve (rounded corner) with radius [0.2,1000]. When there is a corner radius,
 *  the aircraft will never  go through the waypoint. By default, the radius is 0.2
 *  m. The radius should not be larger than the three  dimensional distance between
 *  any two of the three waypoints that comprise the corner.
 */
@property(nonatomic, assign) float cornerRadiusInMeters;


/**
 *  Determines whether the aircraft will turn clockwise or anitclockwise when
 *  changing its heading.
 */
@property(nonatomic) DJIWaypointTurnMode turnMode;


/**
 *  Gimbal pitch angle when reached this waypoint. This property is used when the
 *  `DJIWaypointMission` property `rotateGimbalPitch` is YES . Value should in range
 *  [-90, 0] degree.
 */
@property(nonatomic, assign) float gimbalPitch;




/**
 *  The base automatic speed of the aircraft as it moves between this waypoint and
 *  the next waypoint with range  [0, 15] m/s. By default, it is 0.0 and the
 *  aircraft will fly with `autoFlightSpeed` of  the waypoint mission. If greater
 *  than 0, 'speed' will override `autoFlightSpeed`.  This 'speed' can only define
 *  movement forward through the waypoint mission in comparison  to
 *  `autoFlightSpeed` which can be both forward and backwards through a waypoint
 *  mission.
 *   Waypoint mission speed priority from highest to lowest is:
 *   1) manual speed adjustment  with remote controller joy sticks
 *   2) 'speed'
 *   3) `setAutoFlightSpeed:withCompletion`
 *    4) `autoFlightSpeed`
 *   Warning: 'speed', `shootPhotoTimeInterval`  and `shootPhotoDistanceInterval`
 *  relate to behavior between this waypoint and the next  waypoint in the mission.
 *  In comparison, `turnMode`, `altitude`  and `heading` relate to behavior between
 *  the last waypoint and this waypoint in the waypoint  mission. Only supported by
 *  flight controller firmware 3.2.10.0 or above.
 */
@property(nonatomic, assign) float speed;


/**
 *  The time interval in seconds when two photos are taken as the aircraft moves
 *  between the current waypoint  and the next waypoint. The first photo will be
 *  taken as the aircraft leaves the current waypoint. The  maximum value is
 *  6,000.0. The minimum value is above 0.0 and depends on the camera type and the
 *  camera  parameters. When the photo file format is JPEG, the recommended minimum
 *  value is 2.0. When the photo file  format is RAW, the minimum value is 10.0. If
 *  the input exceeds the camera's capability, the pictures will  be taken at the
 *  maximum possible speed. The default value is 0.0 and no photo will be taken. For
 *  a  waypoint, either `shootPhotoTimeInterval` or `shootPhotoDistanceInterval`  is
 *  0.0. Input with precision of greater than 1 decimal places, will be rounded to
 *  1. Warning: 'speed', `shootPhotoTimeInterval`  and `shootPhotoDistanceInterval`
 *  relate to behavior between this waypoint and the next waypoint  in the mission.
 *  In comparison, `turnMode`, `altitude` and `heading`  relate to behavior between
 *  the last waypoint and this waypoint in the waypoint mission. Only supported by
 *  flight  controller firmware 3.2.10.0 or above.
 */
@property(nonatomic, assign) float shootPhotoTimeInterval;


/**
 *  The distance interval in meters when two photos are taken as the aircraft moves
 *  between the current  waypoint and the next waypoint. The maximum value is
 *  6,000.0. The minimum value is above 0.0 and depends  on the camera type, the
 *  camera parameters and the flight speed. When the photo file format is JPEG, the
 *  time interval between two photos cannot smaller than 2 seconds. When the photo
 *  file format is RAW, the  time interval between two photos cannot smaller than 10
 *  seconds. If the input exceeds the camera's  capability, the taken photos may be
 *  less than expectation. The default value is 0.0 and no photo will be  taken. For
 *  a waypoint, either `shootPhotoTimeInterval`  or `shootPhotoDistanceInterval` is
 *  0.0. Input with precision of greater than 1 decimal  places, will be rounded to
 *  1. Warning: 'speed', `shootPhotoTimeInterval`  and `shootPhotoDistanceInterval`
 *  relate to behavior between this waypoint and the next  waypoint in the mission.
 *  In comparison, `turnMode`, `altitude`  and `heading` relate to behavior between
 *  the last waypoint and this waypoint in the waypoint  mission. Only supported by
 *  flight controller firmware 3.2.10.0 or above.
 */
@property(nonatomic, assign) float shootPhotoDistanceInterval;


/**
 *  Array of all waypoint actions for the respective waypoint. The waypoint actions
 *  will be executed  consecutively from the start of the array once the aircraft
 *  reaches the waypoint.
 */
@property(nonatomic, readonly) NSArray *waypointActions;


/**
 *  Initiate instance with specific waypoint.
 *  
 *  @param coordinate Coordinate Object.
 *  
 *  @return A `DJIWaypoint` object initialized with CLLocationCoordinate2D struct.
 */
- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate;


/**
 *  Adds a waypoint action to a waypoint. The number of waypoint actions should not
 *  be larger  than `DJIMaxActionCount`. The action will only be executed when the
 *  mission's `flightPathMode` property is set  to
 *  `DJIWaypointMissionFlightPathNormal` and will not be executed when the
 *  mission's `flightPathMode` property is set  to
 *  `DJIWaypointMissionFlightPathCurved`. The maximum number of waypoint  actions
 *  you can add is 15.
 *  
 *  @param action Waypoint action to be added to the waypoint.
 *  
 *  @return `YES` if the waypoint action has been added to the waypoint. `NO`  if the waypoint action count is too high, or if the waypoint action was incorrectly setup.
 */
- (BOOL)addAction:(DJIWaypointAction *)action;


/**
 *  Insert a waypoint action at index. @return `YES`, if the waypoint action has
 *  been  inserted. `NO` if the waypoint action count is too high or the index is
 *  invalid.
 *  
 *  @param action Waypoint action to be inserted to the waypoint.
 *  @param index Index of the inserted action.
 *  
 *  @return A boolean value.
 */
- (BOOL)insertAction:(DJIWaypointAction *)action atIndex:(int)index;


/**
 *  Removes a waypoint action from the waypoint. @return `YES` if the waypoint
 *  action  has been removed from the waypoint.
 *  
 *  @param action Waypoint action to be removed from the waypoint.
 *  
 *  @return A boolean value.
 */
- (BOOL)removeAction:(DJIWaypointAction *)action;


/**
 *  Removes a waypoint action from the waypoint by index. After removal, all actions
 *  higher than the index will  be shifted down by one.
 *  
 *  @param index The index of the waypoint action to be removed.
 *  
 *  @return `YES` if waypoint action has been removed from the waypoint.
 */
- (BOOL)removeActionAtIndex:(int)index;


/**
 *  Remove all the actions.
 */
- (void)removeAllActions;

@end

NS_ASSUME_NONNULL_END
