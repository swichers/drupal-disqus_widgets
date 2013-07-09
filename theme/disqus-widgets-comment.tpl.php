<?php
/**
 * @file
 * Theme an individual Disqus comment.
 */
?>
<div class="disqus-comment">
  <span class="disqus-author"><?= theme('disqus_widgets_author', array('author' => $comment->author)) ?></span>
  <span class="disqus-created-at">Posted <?= format_date(strtotime($comment->createdAt), 'short') ?></span>
  <span class="disqus-message"><?= $comment->message ?></span>
</div>
