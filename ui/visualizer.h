#pragma once
/** @file      visualizer.h
 *  @brief     Header file for the visualizer functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/03/29
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include <string>
#include <vector>

/**
 * @brief Retrieves serial communication data and plots it in a viewer.
 *
 * This function retrieves data from a serial communication source and plots it
 * in a viewer for visualization. It reads the incoming data, processes it, and
 * then displays it in a graphical viewer.
 *
 * @return void
 */
void plot(void);

/**
 * @brief Gets the currently selected plot view mode
 * @return 0 for combined view, 1+ for individual channel views
 */
int getCurrentPlotView(void);

/**
 * @brief Sets the current plot view mode
 * @param view 0 for combined view, 1+ for individual channel views
 */
void setCurrentPlotView(int view);

/**
 * @brief Gets the number of available plot views (combined + individual channels)
 * @return Total number of plot views
 */
int getNumberOfPlotViews(void);

/**
 * @brief Gets the name of a specific plot view
 * @param viewIndex Index of the plot view
 * @return Name of the plot view
 */
std::string getPlotViewName(int viewIndex);

/**
 * @brief Renders individual channel plot windows that can be detached/docked
 */
void renderIndividualPlotWindows(void);

/**
 * @brief Gets the number of visible individual plot views
 * @return Number of visible individual plot views
 */
int getNumberOfVisiblePlotViews(void);

/**
 * @brief Gets the name of a visible plot view by index
 * @param visibleIndex Index of the visible plot view (0-based)
 * @return Name of the plot view
 */
std::string getVisiblePlotViewName(int visibleIndex);

/**
 * @brief Gets the channel index for a visible plot view
 * @param visibleIndex Index of the visible plot view (0-based)
 * @return Channel index (-1 if not found)
 */
int getVisiblePlotViewChannelIndex(int visibleIndex);
