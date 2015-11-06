//
//  RenderView.h
//  Descent
//
//  Created by Devin Tuchsen on 10/19/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RenderView : UIView

#ifdef OGLES
- (void)drawView;
@property EAGLContext* context;
@property GLuint colorRenderBuffer;
#endif

@end
