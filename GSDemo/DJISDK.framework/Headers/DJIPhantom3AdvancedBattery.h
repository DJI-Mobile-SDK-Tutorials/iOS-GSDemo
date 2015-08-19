//
//  DJIPhantom3AdvancedBattery.h
//  DJISDK
//
//  Copyright (c) 2015年 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>

@interface DJIPhantom3AdvancedBattery : DJIBattery

/**
 *  Get cell's voltage. The object in cellArray is type of class DJIBatteryCell
 *
 *  @param block Remote execute result
 */
-(void) getCellVoltagesWithResult:(void(^)(NSArray* cellArray, DJIError* error))block;

@end
