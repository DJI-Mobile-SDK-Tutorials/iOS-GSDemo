//
//  DJIWaypointConfigViewController.m
//  GSDemo
//
//  Created by DJI on 12/7/15.
//  Copyright (c) 2015 DJI. All rights reserved.
//

#import "DJIWaypointConfigViewController.h"

@interface DJIWaypointConfigViewController ()

@end

@implementation DJIWaypointConfigViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    [self initUI];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initUI
{
    self.altitudeTextField.text = @"20"; //Set the altitude to 20
    self.autoFlightSpeedTextField.text = @"8"; //Set the autoFlightSpeed to 8
    self.maxFlightSpeedTextField.text = @"10"; //Set the maxFlightSpeed to 10
    [self.actionSegmentedControl setSelectedSegmentIndex:1]; //Set the finishAction to DJIWaypointMissionFinishedGoHome
    [self.headingSegmentedControl setSelectedSegmentIndex:0]; //Set the headingMode to DJIWaypointMissionHeadingAuto
    
}

- (IBAction)cancelBtnAction:(id)sender {
 
    if ([_delegate respondsToSelector:@selector(cancelBtnActionInDJIWaypointConfigViewController:)]) {
        [_delegate cancelBtnActionInDJIWaypointConfigViewController:self];
    }
}

- (IBAction)finishBtnAction:(id)sender {
    
    if ([_delegate respondsToSelector:@selector(finishBtnActionInDJIWaypointConfigViewController:)]) {
        [_delegate finishBtnActionInDJIWaypointConfigViewController:self];
    }
    
}

@end
