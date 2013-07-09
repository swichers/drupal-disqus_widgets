<?php
/**
 * @file
 */

/**
 * hook_block_view() helper for the recent comments block.
 */
function disqus_widgets_disqus_recent_block_view() {

  $block = array();
  $block['subject'] = t('Recent Comments');
  $block['content'] = disqus_widgets_disqus_recent_helper(TRUE);

  return $block;
}

/**
 * hook_block_view() helper for the global recent comments block.
 */
function disqus_widgets_disqus_recent_global_block_view() {

  $block = array();
  $block['subject'] = t('Global Recent Comments');
  $block['content'] = disqus_widgets_disqus_recent_helper(FALSE);

  return $block;
}

/**
 * Helper function to grab recent comments globally or by page.
 *
 * Used to maintain one piece of logic instead of duplicating it.
 *
 * @param boolean $byPage
 *   TRUE to filter by the current page, FALSE to show all.
 *
 * @return array|NULL
 *   A render array on results, NULL on nothing.
 */
function disqus_widgets_disqus_recent_helper($byPage = FALSE) {

  $result = NULL;
  $url = $byPage ? url(current_path(), array('absolute' => TRUE)) : NULL;
  $comments = disqus_widgets_get_comments(3, $url);

  if (!empty($comments)) {

    $result = array(
      '#theme' => 'item_list',
      '#items' => array(),
    );

    foreach ($comments as $comment) {

      $result['#items'][] = theme('disqus_widgets_comment', array(
        'comment' => $comment,
      ));
    }
  }

  return $result;
}
