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
 * hook_block_view() helper for the commenting area.
 */
function disqus_widgets_disqus_comment_area_view() {

  $block = array();
  $block['subject'] = t('Comments');

  $shortname = variable_get('disqus_forum');
  if (empty($shortname)) {

    return $block;
  }

  $identifier = current_path();

  $block['content'] = array('#markup' => theme('disqus_widgets_comment_area', array(
    'shortname' => $shortname,
    'identifier' => $identifier,
  )));

  $disqus_config = 'var disqus_shortname = ' . drupal_json_encode($shortname) . ';';
  $disqus_config .= 'var disqus_identifier = ' . drupal_json_encode($identifier) . ';';

  $block['content']['#attached'] = array(
    'js' => array(
      $disqus_config => array(
        'type' => 'inline',
        'scope' => 'header',
        'group' => JS_LIBRARY,
        'weight' => 0,
      ),
      "//${shortname}.disqus.com/embed.js" => array(
        'type' => 'external',
        'scope' => 'footer',
        'group' => JS_LIBRARY,
        'async' => TRUE,
        'weight' => 1,
      ),
    ),
  );

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

      $date = theme('disqus_widgets_comment_date', array(
        'comment' => $comment,
        'date' => $comment->createdAt,
      ));

      $author = theme('disqus_widgets_author', array(
        'author' => $comment->author,
      ));

      $message = theme('disqus_widgets_message', array(
        'comment' => $comment,
        'message' => $comment->message,
      ));

      $result['#items'][] = theme('disqus_widgets_comment', array(
        'comment' => $comment,
        'message' => $message,
        'author' => $author,
        'date' => $date,
      ));
    }
  }

  return $result;
}
