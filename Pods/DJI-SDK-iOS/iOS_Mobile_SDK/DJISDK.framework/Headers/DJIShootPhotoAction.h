//
//  DJIShootPhotoAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The error domain used for all errors specific to `DJIShootPhotoAction`.
 */
extern const NSErrorDomain DJIShootPhotoActionErrorDomain;


/**
 *  Error codes for `DJIShootPhotoAction` specific errors.
 */
typedef NS_ENUM(NSInteger, DJIShootPhotoActionError) {

    /**
     *  Default error in case no other matches.
     */
    DJIShootPhotoActionErrorUnknown = -1,


    /**
     *  Invalid value for photo count.
     */
    DJIShootPhotoActionErrorInvalidPhotoCount = 100,


    /**
     *  Invalid value for time interval.
     */
    DJIShootPhotoActionErrorInvalidTimeInterval = 101
};


/**
 *  This class represents a shoot photo action used as an element in a Timeline
 *  mission. By creating an object of this class and adding it to Mission Control's
 *  Timeline,  the camera can shoot a photo when the Timeline reaches the action.
 */
@interface DJIShootPhotoAction : DJIMissionAction


/**
 *  Initialize object to shoot a single photo.
 *  
 *  @return An instance of `DJIShootPhotoAction`.
 */
- (instancetype _Nullable)initWithSingleShootPhoto;


/**
 *  Initialize object to shoot multiple photos.
 *  
 *  @param count Photo count.
 *  @param interval Time interval in seconds between shooting photos.
 *  
 *  @return An instance of `DJIShootPhotoAction`.
 */
- (instancetype _Nullable)initWithPhotoCount:(int)count timeInterval:(double)interval;

@end

NS_ASSUME_NONNULL_END
