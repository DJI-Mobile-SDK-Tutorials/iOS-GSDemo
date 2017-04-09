//
//  DJITakeOffAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>


/**
 *  This class represents a take-off action used as an element in a Timeline
 *  mission. By creating an object of this class and adding it to Mission Control's
 *  Timeline,  the aircraft will take-off when the Timeline reaches the action.
 */
@interface DJITakeOffAction : DJIMissionAction

@end
